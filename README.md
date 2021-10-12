# fmilib-cpp wrapper

Simplified and object-oriented C++ wrapper for [FMI Library](https://github.com/modelon-community/fmi-library).

### Building

fmilib-cpp uses [conan](https://conan.io/) under-the-hood for managing dependencies.

```
pip install conan
```

Make sure to add osp as a remote prior to configuring the project:
```
conan remote add osp https://osp.jfrog.io/artifactory/api/conan/conan-local
```

### Installing

`fmilibcpp` is available through the conan remote ais:

`conan remote add ais https://ais.jfrog.io/artifactory/api/conan/ais-conan-local`

Then add a dependency to: </br>
`fmilibcpp/<version>@ais/stable` (stable channel -> releases) </br>
`fmilibcpp/<version>@ais/testing` (development builds -> master) </br>
`fmilibcpp/<version>@ais/testing-<branch>` (development builds -> branches)


Additionally, you can of course build, include and link to it as any other
CMake project or include it as a subproject in your own CMake project.

