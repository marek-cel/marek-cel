from setuptools import setup, find_packages


with open("LICENSE") as f:
    license = f.read()

setup(
    name="sample_project",
    version="1.0.0",
    description="Sample package",
    author="John Doe",
    author_email="jdoe@mail.com",
    url="https://sample.com",
    license=license,
    packages=find_packages(exclude=["tests", "*.tests", "*.tests.*", "tests.*"]),
    install_requires=["PyQt5", "numpy"],
    entry_points = {
        "console_scripts": [
            "sample-project = sample_project.core:main",                  
        ],              
    }
)