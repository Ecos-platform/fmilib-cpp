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

`fmilibcpp` is avilable through the conan remote ais:

`conan remote add ais https://ais.jfrog.io/artifactory/api/conan/ais-conan-local`

Then add a dependency to: `fmilibcpp/<version>@ais/testing`

