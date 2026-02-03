#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/Neuron.h"
#include "aicpp/utility.h"

namespace py = pybind11;

using namespace aicpp;

std::any py_to_any(py::object obj)
{
    if (py::isinstance<py::bool_>(obj))
        return std::any(obj.cast<bool>());
    else if (py::isinstance<py::int_>(obj))
        return std::any(obj.cast<int>());
    else if (py::isinstance<py::float_>(obj))
        return std::any(obj.cast<double>());
    else if (py::isinstance<py::str>(obj))
        return std::any(obj.cast<std::string>());

    // numpy array → Eigen::MatrixXi
    try
    {
        auto arr = obj.cast<py::array_t<int> >();
        Eigen::MatrixXi const mat = Eigen::Map<Eigen::MatrixXi>(
            arr.mutable_data(),
            arr.shape(0),
            arr.shape(1)
            );

        return std::any(mat);
    }
    catch (...)
    {
    }

    if (py::isinstance<py::list>(obj))
    {
        py::list const lst = obj.cast<py::list>();

        if (lst.size() > 0)
        {
            if (py::isinstance<py::array>(lst[0]))
            {
                // list[np.ndarray] → std::vector<Eigen::MatrixXi>
                std::vector<Eigen::MatrixXi> vec;
                vec.reserve(lst.size());

                for (auto const& item : lst)
                {
                    auto arr = item.cast<py::array_t<int> >();

                    Eigen::MatrixXi const mat = Eigen::Map<Eigen::MatrixXi>(
                        arr.mutable_data(),
                        arr.shape(0),
                        arr.shape(1)
                        );
                    vec.emplace_back(mat);
                }

                return std::any(vec);
            }
            else if (py::isinstance<py::list>(lst[0]))
            {
                py::list const lst1 = lst[0].cast<py::list>();

                if (lst1.size() > 0)
                {
                    if (py::isinstance<py::tuple>(lst1[0]))
                    {
                        py::tuple const first_tuple = lst1[0].cast<py::tuple>();

                        if (py::isinstance<py::tuple>(first_tuple[0]) &&
                            py::isinstance<py::tuple>(first_tuple[1]))
                        {
                            py::tuple const tuple1 = first_tuple[0].cast<py::tuple>();
                            py::tuple const tuple2 = first_tuple[1].cast<py::tuple>();

                            if (py::isinstance<py::int_>(tuple1[0]) &&
                                py::isinstance<py::int_>(tuple1[1]) &&
                                py::isinstance<py::int_>(tuple2[0]) &&
                                py::isinstance<py::int_>(tuple2[1]))
                            {
                                std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > vec;

                                for (auto const& item : lst)
                                {
                                    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > v;
                                    v.reserve(lst1.size());

                                    for (auto const& item1 : lst1)
                                    {
                                        py::tuple const tup = item1.cast<py::tuple>();
                                        py::tuple const tup1 = tup[0].cast<py::tuple>();
                                        py::tuple const tup2 = tup[1].cast<py::tuple>();

                                        v.emplace_back(std::make_pair(std::make_pair(tup1[0].cast<py::int_>(), tup1[1].cast<py::int_>()),
                                                                      std::make_pair(tup2[0].cast<py::int_>(), tup2[1].cast<py::int_>())));
                                    }

                                    vec.emplace_back(v);
                                }

                                return std::any(vec);
                            }
                        }
                    }
                    else if (py::isinstance<py::list>(lst1[0]))
                    {
                        py::list const lst2 = lst1[0].cast<py::list>();

                        if (lst2.size() > 0)
                        {
                            if (py::isinstance<py::tuple>(lst2[0]))
                            {
                                py::tuple const first_tuple = lst2[0].cast<py::tuple>();

                                if (first_tuple.size() == 2)
                                {
                                    if (py::isinstance<py::int_>(first_tuple[0]) &&
                                        py::isinstance<py::int_>(first_tuple[1]))
                                    {
                                        std::vector<std::vector<std::vector<std::pair<int, int> > > > vec;

                                        for (auto const& item : lst)
                                        {
                                            std::vector<std::vector<std::pair<int, int> > > vec1;
                                            vec1.reserve(lst1.size());

                                            for (auto const& item1 : lst1)
                                            {
                                                std::vector<std::pair<int, int> > vec2;
                                                vec2.reserve(lst2.size());

                                                for (auto const& item2 : lst2)
                                                {
                                                    py::tuple const tup = item2.cast<py::tuple>();

                                                    vec2.emplace_back(tup[0].cast<py::int_>(), tup[1].cast<py::int_>());
                                                }

                                                vec1.emplace_back(vec2);
                                            }

                                            vec.emplace_back(vec1);
                                        }

                                        return std::any(vec);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (py::isinstance<py::tuple>(lst[0]))
            {
                // list[tuple[np.ndarray, np.ndarray]] → std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >
                py::tuple const first_tuple = lst[0].cast<py::tuple>();

                if (first_tuple.size() == 2)
                {
                    if (py::isinstance<py::int_>(first_tuple[0]) &&
                        py::isinstance<py::int_>(first_tuple[1]))
                    {
                        std::vector<std::pair<int, int> > vec;

                        for (auto const& item : lst)
                        {
                            py::tuple const tup = item.cast<py::tuple>();

                            vec.emplace_back(tup[0].cast<py::int_>(), tup[1].cast<py::int_>());
                        }

                        return std::any(vec);
                    }
                    else if (py::isinstance<py::array>(first_tuple[0])
                             && py::isinstance<py::array>(first_tuple[1]))
                    {
                        std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > vec;

                        for (auto const& item : lst)
                        {
                            py::tuple const tup = item.cast<py::tuple>();

                            auto arr1 = tup[0].cast<py::array_t<int> >();
                            Eigen::MatrixXi const mat1 = Eigen::Map<Eigen::MatrixXi>(
                                arr1.mutable_data(),
                                arr1.shape(0),
                                arr1.shape(1)
                                );

                            auto arr2 = tup[1].cast<py::array_t<int> >();
                            Eigen::MatrixXi const mat2 = Eigen::Map<Eigen::MatrixXi>(
                                arr2.mutable_data(),
                                arr2.shape(0),
                                arr2.shape(1)
                                );

                            vec.emplace_back(mat1, mat2);
                        }

                        return std::any(vec);
                    }
                }
            }
        }
    }

    // dict[int, int] → std::map<int, int>
    if (py::isinstance<py::dict>(obj))
    {
        auto const dict{obj.cast<py::dict>()};

        if (dict.size()
            && py::isinstance<py::int_>(dict.begin()->first)
            && py::isinstance<py::int_>(dict.begin()->second))
        {
            std::map<int, int> mapping;

            for (auto const& item : dict)
                mapping[item.first.cast<int>()] = item.second.cast<int>();

            return std::any(mapping);
        }
    }

    throw std::runtime_error("Unsupported type for conversion to std::any");
}

py::object any_to_py(std::any const& a)
{
    if (a.type() == typeid(bool))
        return py::cast(std::any_cast<bool>(a));
    else if (a.type() == typeid(int))
        return py::cast(std::any_cast<int>(a));
    else if (a.type() == typeid(double))
        return py::cast(std::any_cast<double>(a));
    else if (a.type() == typeid(std::string))
        return py::cast(std::any_cast<std::string>(a));

    // Eigen::MatrixXi → numpy array
    if (a.type() == typeid(Eigen::MatrixXi))
    {
        auto const mat = std::any_cast<Eigen::MatrixXi>(a);

        return py::cast(mat);
    }

    // std::vector<Eigen::MatrixXi> → list[np.ndarray]
    if (a.type() == typeid(std::vector<Eigen::MatrixXi>))
    {
        auto const vec = std::any_cast<std::vector<Eigen::MatrixXi> >(a);
        py::list result;

        for (auto const& mat : vec)
            result.append(py::cast(mat));

        return result;
    }

    // std::vector<std::pair<int, int> > → list[tuple[int, int]]
    if (a.type() == typeid(std::vector<std::pair<int ,int> >))
    {
        auto const vec = std::any_cast<std::vector<std::pair<int, int> > >(a);
        py::list result;

        for (auto const& [mat1, mat2] : vec)
            result.append(py::make_tuple(py::cast(mat1), py::cast(mat2)));

        return result;
    }

    // std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > → list[tuple[np.ndarray, np.ndarray]]
    if (a.type() == typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >))
    {
        auto const vec = std::any_cast<std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > >(a);
        py::list result;

        for (auto const& [mat1, mat2] : vec)
            result.append(py::make_tuple(py::cast(mat1), py::cast(mat2)));

        return result;
    }

    // std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > → list[list[tuple[tuple[int, int], tuple[int, int]]]]
    if (a.type() == typeid(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >))
    {
        auto const vec = std::any_cast<std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > >(a);
        py::list result;

        for (auto const& vec1 : vec)
        {
            py::list l;

            for (auto const& [p1, p2] : vec1)
                l.append(py::make_tuple(py::make_tuple(p1.first, p1.second),
                                        py::make_tuple(p2.first, p2.second)));

            result.append(l);
        }

        return result;
    }

    // std::vector<std::vector<std::vector<std::pair<int, int> > > > → list[list[list[tuple[int, int]]]]
    if (a.type() == typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >))
    {
        auto const vec = std::any_cast<std::vector<std::vector<std::vector<std::pair<int, int> > > > >(a);
        py::list result;

        for (auto const& vec1 : vec)
        {
            for (auto const& vec2 : vec1)
            {
                for (auto const& [i, j] : vec2)
                    result.append(py::make_tuple(i, j));
            }
        }


        return result;
    }

    // std::map<int, int> → dict
    if (a.type() == typeid(std::map<int, int>))
    {
        auto const map = std::any_cast<std::map<int, int> >(a);
        py::dict result;

        for (auto const& [k, v] : map)
            result[py::cast(k)] = py::cast(v);

        return result;
    }

    return py::none();
}

class PyNeuron : public Neuron
{
    public:
        PyNeuron(std::string const& name,
                 py::function py_func,
                 std::vector<std::type_index> const& inputTypes,
                 std::type_index const& outputType)
            : Neuron(name,
                     [py_func] (std::vector<std::any> const& args) -> std::any
                     {
                         py::list py_args;

                         for (auto const& arg : args)
                             py_args.append(any_to_py(arg));

                         py::object result = py_func(*py_args);

                         return py_to_any(result);
                     },
                     inputTypes,
                     outputType)
        {
        }
};

PYBIND11_MODULE(pyaicpp, m)
{
    m.doc() = "Artificial intelligence with a network of connected neurons in C++ with Python bindings for aicpp";

    py::class_<Neuron>(m, "Neuron")
        .def(py::init<std::string const&,
                      std::function<std::any(std::vector<std::any>)> const&,
                      std::vector<std::type_index> const&,
                      std::type_index const&>())
        .def("name", &Neuron::name)
        .def("inputTypes", &Neuron::inputTypes)
        .def("outputType", &Neuron::outputType);

    py::class_<PyNeuron, Neuron>(m, "PyNeuron")
        .def(py::init<std::string const&,
                      py::function,
                      std::vector<std::type_index> const&,
                      std::type_index const&>(),
             py::arg("name"),
             py::arg("function"),
             py::arg("inputTypes"),
             py::arg("outputType"))
        .def("name", &PyNeuron::name);

    py::class_<Connection>(m, "Connection")
        .def("neuron", &Connection::neuron)
        .def("inputs", &Connection::inputs)
        .def("cost", &Connection::cost)
        .def("depth", &Connection::depth, py::arg("d") = 0)
        .def("string", &Connection::string)
        .def("inputTypes", &Connection::inputTypes)
        .def("output", [] (Connection const& c) -> py::object
             {
                 return any_to_py(c.output());
             });

    py::class_<Brain>(m, "Brain")
        .def(py::init<std::vector<std::reference_wrapper<Neuron const> > const&>())
        .def("learn", [] (Brain const& brain,
                          std::vector<py::object> const& py_targets,
                          size_t level,
                          double eps) -> std::vector<Connection>
             {
                 std::vector<std::any> targets;
                 targets.reserve(py_targets.size());

                 for (auto const& py_target : py_targets)
                     targets.emplace_back(py_to_any(py_target));

                 py::gil_scoped_release release;

                 return brain.learn(targets, level, eps);
             },
             py::arg("targets"),
             py::arg("level") = 3,
             py::arg("eps") = 1e-6);

    m.def("heuristic", [] (py::object val, py::object target) -> double
    {
        auto const any_val = py_to_any(val);
        auto const any_target = py_to_any(target);

        return heuristic(any_val, any_target);
    });

    py::class_<std::type_index>(m, "TypeIndex")
        .def(py::init<std::type_info const&>());

    m.def("type_index_from_name", [] (std::string const& name) -> std::type_index
    {
        if (name == "int") return typeid(int);
        if (name == "double") return typeid(double);
        if (name == "bool") return typeid(bool);
        if (name == "str") return typeid(std::string);
        if (name == "numpy.ndarray") return typeid(Eigen::MatrixXi);
        if (name == "list[numpy.ndarray]") return typeid(std::vector<Eigen::MatrixXi>);
        if (name == "list[tuple[numpy.ndarray, numpy.ndarray]]") return typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >);
        if (name == "dict[int, int]") return typeid(std::map<int, int>);
        if (name == "list[list[list[tuple[int, int]]]]") return typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >);
        if (name == "list[list[tuple[tuple[int, int], tuple[int, int]]]]") return typeid(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >);
        throw std::runtime_error("Unknown type name: " + name);
    });
}
