from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import os

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):
    def run(self):
        for ext in self.extensions:
            self.build_cmake(ext)

    def build_cmake(self, ext):
        import subprocess
        import pathlib
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        cfg = 'Release'
        cmake_args = [
            f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}',
            f'-DCMAKE_BUILD_TYPE={cfg}',
            f'-DPYTHON_EXECUTABLE={sys.executable}',
        ]
        build_args = ['--config', cfg]
        os.makedirs(self.build_temp, exist_ok=True)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

setup(
    name='pyaicpp',
    version='0.1',
    author='Julien LIVET',
    description='Artificial intelligence with a network of connected neurons in C++ with Python bindings',
    ext_modules=[CMakeExtension('pyaicpp')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
)
