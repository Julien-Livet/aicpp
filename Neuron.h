#ifndef NEURON_H
#define NEURON_H

#include <any>
#include <cassert>
#include <chrono>
#include <functional>
#include <string>
#include <variant>

#include <Eigen/Core>

template <class R, class... Args>
class Neuron;

using AnyNeuron = std::variant<
    Neuron<bool>,
    Neuron<bool, bool>,
    Neuron<bool, bool, bool>,
    Neuron<bool, char, char>,
    Neuron<bool, double, double>,
    Neuron<bool, float, float>,
    Neuron<bool, int, int>,
    Neuron<bool, long, long>,
    Neuron<bool, std::string>,
    Neuron<char>,
    Neuron<char, char>,
    Neuron<char, char, char>,
    Neuron<char, float>,
    Neuron<char, double>,
    Neuron<char, int>,
    Neuron<char, long>,
    Neuron<char, std::string>,
    Neuron<double>,
    Neuron<double, char>,
    Neuron<double, char, char>,
    Neuron<double, double>,
    Neuron<double, double, double>,
    Neuron<double, Eigen::MatrixXd>,
    Neuron<double, Eigen::MatrixXd, std::pair<int, int> >,
    Neuron<double, float>,
    Neuron<double, int>,
    Neuron<double, int, int>,
    Neuron<double, long>,
    Neuron<double, long, long>,
    Neuron<double, std::string>,
    Neuron<float>,
    Neuron<float, char>,
    Neuron<float, double>,
    Neuron<float, float>,
    Neuron<float, float, float>,
    Neuron<float, Eigen::MatrixXf>,
    Neuron<float, Eigen::MatrixXf, std::pair<int, int> >,
    Neuron<float, int>,
    Neuron<float, long>,
    Neuron<float, std::string>,
    Neuron<int>,
    Neuron<int, char>,
    Neuron<int, double>,
    Neuron<int, float>,
    Neuron<int, int>,
    Neuron<int, int, int>,
    Neuron<int, Eigen::MatrixXi>,
    Neuron<int, Eigen::MatrixXi, std::pair<int, int> >,
    Neuron<int, long>,
    Neuron<int, std::string>,
    Neuron<Eigen::MatrixXd>,
    Neuron<Eigen::MatrixXd, int, double>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, std::pair<int, int>, double>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, std::vector<std::pair<int, int> >, double>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, double>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, double, double>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, int, double>,
    Neuron<Eigen::MatrixXd, Eigen::MatrixXd, int, int>,
    Neuron<Eigen::MatrixXd, std::pair<int, int> >,
    Neuron<Eigen::MatrixXf>,
    Neuron<Eigen::MatrixXf, int, float>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, std::pair<int, int>, float>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, std::vector<std::pair<int, int> >, float>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, float>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, float, float>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, Eigen::MatrixXf>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, int, float>,
    Neuron<Eigen::MatrixXf, Eigen::MatrixXf, int, int>,
    Neuron<Eigen::MatrixXf, std::pair<int, int> >,
    Neuron<Eigen::MatrixXi>,
    Neuron<Eigen::MatrixXi, int, int>,
    Neuron<Eigen::MatrixXi, Eigen::MatrixXi, std::pair<int, int>, int>,
    Neuron<Eigen::MatrixXi, Eigen::MatrixXi, std::vector<std::pair<int, int> >, int>,
    Neuron<Eigen::MatrixXi, Eigen::MatrixXi>,
    Neuron<Eigen::MatrixXi, Eigen::MatrixXi, Eigen::MatrixXi>,
    Neuron<Eigen::MatrixXi, Eigen::MatrixXi, int>,
    Neuron<Eigen::MatrixXi, Eigen::MatrixXi, int, int>,
    Neuron<Eigen::MatrixXi, std::pair<int, int> >,
    Neuron<long>,
    Neuron<long, char>,
    Neuron<long, double>,
    Neuron<long, float>,
    Neuron<long, int>,
    Neuron<long, long>,
    Neuron<long, long, long>,
    Neuron<long, std::string>,
    Neuron<std::pair<int, int> >,
    Neuron<std::string>,
    Neuron<std::string, bool>,
    Neuron<std::string, char>,
    Neuron<std::string, double>,
    Neuron<std::string, float>,
    Neuron<std::string, int>,
    Neuron<std::string, long>,
    Neuron<std::string, std::string>,
    Neuron<std::string, std::string, std::string>,
    Neuron<std::vector<std::pair<int, int> > >
    >;

class Connection;

using ConnectionInput = std::variant<std::reference_wrapper<AnyNeuron>, Connection, bool, char, double, Eigen::MatrixXd, Eigen::MatrixXf, Eigen::MatrixXi, float, int, long, std::pair<int, int>, std::string>;
using ConnectionOutput = std::any;

template <class R, class... Args>
class Neuron
{
	public:
		bool activated{true};
        std::chrono::time_point<std::chrono::system_clock> const timeStamp{std::chrono::system_clock::now()};
        int limitationTimeout{-1};
        std::function<R(Args...)> function;
        double weight{1.0};

		Neuron() = default;

        Neuron(std::function<R(Args...)> const& function, std::string const& name = std::string{}, std::string const& module = std::string{}, double weight = 1.0) : function{function}, name_{name}, module_{module}, weight{weight}
		{
		}

        std::vector<std::type_info const*> inputTypes() const
        {
            return {&typeid(Args)...};
        }

        std::type_info const& outputType() const
        {
            return typeid(R);
        }

        R output(std::vector<ConnectionOutput> const& args) const
        {
            assert(args.size() == sizeof...(Args));

            return output(args, std::index_sequence_for<Args...>{});
		}

        R output(Args... args) const
        {
            return function(args...);
		}

		std::string const& name() const
		{
			return name_;
		}

		std::string const& module() const
		{
			return module_;
		}

		constexpr size_t countArgs() const
		{
			return sizeof...(Args);
        }

    private:
		std::string name_;
        std::string module_;

		template <std::size_t... I>
        R output(std::vector<ConnectionOutput> const& args, std::index_sequence<I...>) const
		{
            return function(std::any_cast<Args>(args[I])...);
		}
};

#endif // NEURON_H
