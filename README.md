# xlfparser-c
[![Build Status](https://travis-ci.org/ajiwo/xlfparser-c.svg?branch=master)](https://travis-ci.org/ajiwo/xlfparser-c)

[xlf](http://xibo.org.uk/manual-tempel/en/xlf.html) (Xibo Layout Format) parser

## Usage example.

```c
#include <xlfparser/xlfparser.h>

int main() {
    xlfNode *node;
    int num_region, num_tag;

    const char *filepath = "/tmp/file.xlf";
    node = xlfparser_parse_file(filepath, &num_region, &num_tag);

    if(node == NULL) {
        /* ouch cannot parse the file */
        return -1;
    }
    // from here, we almost get everything we need

    Layout *layout = xlfparser_get_layout(node);
    // here we go, we got everything we need here.

    // access layout attributes
    // layout->width
    // layout->height
    // layout->bgcolor
    // etc..

    // get the first region from layout.
    Region *region = xlfparser_get_region(layout, 0);
    // access region attributes
    // region->width
    // region->left
    // region->top
    // etc..

    // get the first media from region
    Media *media = xlfparser_get_media(region, 0);
    // access media attributes
    // media->id
    // media->type
    // media->duration
    // etc..

    // finally, don't forget to delete the layout
    return xlfparser_delete_layout(layout);

}

```

## Dependencies
* [libroxml](http://libroxml.net) or
* [libxml2](http://www.xmlsoft.org)

Either one, but not both, if both libs are available on your system use one of the following during build.
```shell
cmake [source-dir] -DPREFER_LIBROXML=1
```
```shell
cmake [source-dir] -DPREFER_LIBXML2=1
```

## Build and Install
* clone
```shell
    git clone https://github.com/ajiwo/xlfparser-c
```
* build
```shell
    cd xlfparser-c
    mkdir build
    cd build
    cmake ..
    # or
    # cmake .. -DPREFER_LIBROXML=1
    # to explicitly choose libroxml
    # or
    # cmake .. -DPREFER_LIBXML2=1
    # to explicitly choose libxml2
    make
```
* install
```shell
    sudo make install
```
