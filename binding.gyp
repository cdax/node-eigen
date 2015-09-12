{
    'targets': [
        {
            'target_name': 'eigen',
            'sources': [
                'src/eigen.cc',

                'src/Core/matrix.cc'
            ],
            'include_dirs': [
                'deps/eigen-3.2.5'
            ]
        }
    ]
}
