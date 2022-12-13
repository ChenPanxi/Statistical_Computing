# Statistical_Computing: What Is This Repository?

This repository was created to organize files submitted for a final project in BIOSTATS 615 (Statistical Computing) at the University of Michigan: "Line Detection in Point Data Using the Hough Transformation: A Novel R Implementation." Authored by Panxi Chen, Sophia Luo, and Maya Bose (group 12).

# Overview of Contents

## Examples
The quickest way to see how our implementation of the Hough Transform works is to view HoughPost_example.pdf for a visual walkthrough of the functions. You can download HoughPost_example.Rmd to try it out yourself.

## The HoughPost R Package
To download our implementation, ensure you have the `devtools` package installed and loaded, and run: `install_github("ChenPanxi/Statistical_Computing/HoughPost")`
Functions include:
-`simulator`: Randomly generate points in Cartesian coordinates corresponding to either lines or circles, specifying a parameter that controls how "noisy" the points are.
-`hough_space`: Project points into Hough (parameter) space.
-`hough_trans`: Detect lines or circles and plot them on top of original data.

## Old Implementations
We went through several versions of the implementation, overhauling the code at each step for accuracy, efficiency, and style. See what didn't work out in the Old_Implementations folder.
