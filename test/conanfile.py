from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import copy


class dateClassRecipe(ConanFile):
    name = "dateclass"
    version = "0.5.0"

    # Optional metadata
    license = "Apache License Version 2.0"
    author = "Dipl.-Inform. Kai Hofmann <powerstat@web.de>"
    url = "https://github.com/powerstat/DateClass"
    description = "DateClass - value object (immutable) implementation of calendar classes."
    topics = ("calendar", "julian", "gregorian", "C++", "immutable")

    no_copy_source = True
    generators = "CMakeToolchain", "CMakeDeps"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # generators = "CMakeDeps"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "test/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def validate(self):
        check_min_cppstd(self, "17")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            test_folder = os.path.join("test")
            if self.settings.os == "Windows":
                test_folder = os.path.join("test", str(self.settings.build_type))
            self.run(os.path.join(test_folder, "test_dateclass"))


    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "*.h", self.source_folder, self.package_folder)

    def package_info(self):
        self.cpp_info.libs = ["dateClass"]
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

    def package_id(self):
        self.info.clear()

    def requirements(self):
        # self.requires("pkgname/1.0.0")
        self.test_requires("googletest/1.14.0")