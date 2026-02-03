import pyaicpp

digitNeurons = []

for i in range(0, 10):
    digitNeurons.append(pyaicpp.PyNeuron(str(i), lambda i = i: i, [], pyaicpp.type_index_from_name("int")))

addNeuron = pyaicpp.PyNeuron("add", lambda x, y: x + y, [pyaicpp.type_index_from_name("int"), pyaicpp.type_index_from_name("int")], pyaicpp.type_index_from_name("int"))
mulNeuron = pyaicpp.PyNeuron("mul", lambda x, y: x * y, [pyaicpp.type_index_from_name("int"), pyaicpp.type_index_from_name("int")], pyaicpp.type_index_from_name("int"))
intToStrNeuron = pyaicpp.PyNeuron("intToStr", lambda x: str(x), [pyaicpp.type_index_from_name("int")], pyaicpp.type_index_from_name("str"))

def test_str():
    neurons = []
    neurons += digitNeurons
    neurons.append(addNeuron)
    neurons.append(mulNeuron)
    neurons.append(intToStrNeuron)

    b = pyaicpp.Brain(neurons)

    target = "11"

    connections = b.learn([target], level = 2)

    assert(len(connections))

    print(connections[0].string())

    assert(not pyaicpp.heuristic(connections[0].output(), target))

