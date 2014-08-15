# About DocFormats

DocFormats is a library for converting between different word processing file
formats. Currently it supports .docx (part of the OOXML specification), HTML,
and LaTeX (export-only).

The design is based on on the idea of *bidirectional transformation*, in which a
*concrete* document (the original file in its source format) is converted into
an *abstract* document (in the destination format), and a modified version of
the abstract document can then be used to update the concrete document in a
non-destructive manner, keeping intact all parts of the file which are not
supported in the abstract format by only modifying the original file, rather
than replacing it.

At present, its primary use case is for applications which need to convert .docx
files to HTML, modify the HTML in some way, and then update the source .docx
file with the changes that have been made. However, this is just a starting
point, and the intention is to expand this support with the ability to do the
inverse of this, as well as work with other formats like ODF, RTF, and Markdown.

DocFormats start out as part of [UX Write](http://www.uxproductivity.com), a
word processor for the iPad that uses HTML as its native file format, and uses
the library to support editing of Microsoft Word documents. However, the library
has many use cases outside of word processing, and we hope to expand it to
support other related classes of file formats such as spreadsheets,
presentations, and drawings.

The short term goal of the project is to have an easy-to-integrate library that any
application can use to embed support for a range of different file formats, and
use the parsing, serialisation, and conversion facilities for various purposes.
These include editors, batch conversion tools, web publishing systems, document
analysis tools, and content management systems. By abstracting over different
file formats and using HTML as a common intermediate format, you can just code
your application to that, and let DocFormats take care of conversion to other
formats.

The medium term goal of the project is to have a series of end-user applications
(separate from the library itself) including an editor and file conversion tool.
These will serve as examples of how the libraries can be used.

It is also a goal to cooperate with other open source projects, in terms of
getting input from them as well as providing APIs for their use.


# License

DocFormats is licensed under the Apache License version 2.0; see
LICENSE.txt for details.

# What the library can do

1. Create new HTML files from a .docx source
2. Create new .docx files from a HTML source
3. Update existing .docx files based on a modified HTML file produced in (1)
4. Convert .docx or HTML files to LaTeX
5. Provide access to document structure, in terms of a DOM-like API for
   manipulating XML trees, and an object model for working with CSS stylesheets

# Components

There are three major components, in their respective directories:

* `DocFormats` - the library itself
* `dfutil` - a driver program used for running [...]
* automated tests (located in the tests directory)

Run dfutil without any command-line arguments to see a list of operations. Here
is an example of converting a .docx file to HTML, modifying it, and then upating
the original .docx.

    dfutil filename.docx filename.html
    vi filename.xml # Make some changes
    dfutil filename.html filename.docx

If you examine the convertFile function in `dfutil/Commands.c`, you will see the
main entry points to perform these conversions, which you can call from your own
program.

# Current Status

DocFormats has been shipping as part of UX Write on the iOS app store since
February 2013. From this perspective, it is a stable, mature library that works
for the most commonly-used features of .docx formats. As an open source project,
it is completely new, and from this perspective is very much in its early
stages. We are currently exploring the best way to leverage the existing work
that has been done to make it easier to integrate in other projects, as well as
support more file formats.

As a library for use in your application, it should be considered pre-alpha. In
particular, there are likely to be major changes to the API over the coming
months, as we better define [...]

# Platforms and dependencies

DocFormats builds and runs on iOS, OS X, and Linux. Windows support is in the works.

To build DocFormats, you will need to have the following installed:

* [CMake](http://www.cmake.org)
* [libxml2](http://xmlsoft.org)
* [libiconv](https://www.gnu.org/software/libiconv/)
* [zlib](http://www.zlib.net)

# Build instructions
## Building on Linux

Set the DOCFORMATS_DIR environment variable to the location of the repository
root. Then, anywhere on your filesystem:

    mkdir build
    cd build
    cmake -G "Unix Makefiles" $DOCFORMATS_DIR
    make

This will produce two binaries:

* `DocFormats/libDocFormats.a` -- a static library
* `dfutil/dfutil` -- the driver program

Note that, as per standard cmake practice, you should always build separately
from the source tree (although a separate subdirectory within the source tree is
acceptable).

To run the tests, do the following:

    dfutil -test $DOCFORMATS_DIR/tests

## Building on OS X

You can either use the instructions above for building using make, or
alternatively generate an Xcode project:

    mkdir build
    cd build
    cmake -G Xcode $DOCFORMATS__DIR

This will produce DocFormats.xcodeproj, which you can then open in Xcode.

## Building on Windows

Windows is not yet supported.

# Further information

Questions/comments? Contact Peter Kelly
<[peter@uxproductivity.com](mailto:peter@uxproductivity.com)>.
