{
    "targets": [{
        "target_name": "mytools",
        'cflags': [ '-O3', '-std=c++14', '-Wno-unused-variable', '-floop-interchange', '-floop-strip-mine', '-floop-block', '-floop-parallelize-all', '-ftree-parallelize-loops=4' ],
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "myTools.cpp",
            "tools/writeFile.cpp",
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}