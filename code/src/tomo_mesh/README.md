       
## *���������� �� ������ ���������� DCMTK*
��� ����������� ������ ���������� DCMTK, �� ����� ���������� ������ ���� ����������� CMake(https://cmake.org/) � Conan(https://conan.io/). ��������� ����������� �� ���������. ����� ����� ��������� ��������� ������ � ��������� � ����� ��������������� ����������� � ������ �������, ��������� ����.

     $ mkdir build.debug

     $ cd build.debug

     $ conan install ../src -s compiler="Visual Studio" -s compiler.version=14 -s arch=x86 -s build_type=Debug -s compiler.runtime=MDd

     $ cmake ../src -G "Visual Studio 14"

### *����������*
������� �������� � ������ ������������� �� ���������� Visual Studio 14 32bit.
     
### *����������� � ��������*

1. ������� ���������� � ������ build.debug.
2. ��������� � ��� ����������.
3. Conan ���������� ���������� � ��������� ����� ����������.
4. CMake ������ ������ ����������.




