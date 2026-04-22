def pytest_addoption(parser):
    parser.addoption("--mode", action = "store", default = "default")
    parser.addoption("--provider", action = "store")
    parser.addoption("--model", action = "store")
    parser.addoption("--dslMemory", action = "store")
