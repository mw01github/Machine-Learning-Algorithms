from distutils.core import setup, Extension


def main():
    setup(
        name='mymodule',
        version='1.0.0',
        description='Module Description!!',
        author='Temp Name',
        author_email='temp@mail.com',
        ext_modules=[Extension('mymodule', ['TestMod.c'])]
    )


if __name__ == "__main__":
    main()
