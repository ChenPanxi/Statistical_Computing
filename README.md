# Statistical_Computing: What Is This Repository?

This repository was created to organize files submitted for a final project in BIOSTATS 615 (Statistical Computing) taught by Dr. Hyun Min Kang at the University of Michigan: "Line Detection in Point Data Using the Hough Transformation: A Novel R Implementation." Authored by Panxi Chen, Sophia Luo, and Maya Bose (group 12). [The formal report can be found here.](https://docs.google.com/document/d/1x8tjiKyTV1YRHhuBsW-YlDhcexBaT0P2vgnaXSWaqQc/edit?usp=sharing)

# Motivation

Panxi Chen's research involves analysis of images of human tissue samples with hand-labeled abnormalities. The analysis of patterns of abnormalities could potentially be made more efficient and accurate than human review with the help of computational feature extraction methods. However, the Hough Transform has typically been applied to images and we could not find any publicly available implementations that take point coordinates as input instead of images. Although coordinates can be roughly converted to images using any statistical software capabable of plotting points, current image-based implementations are not robust to the noisy images that result from this conversion. Hence, a robust implmentation of the Hough Transform is necessary for the efficient and accurate analysis of the tissue samples under review.

# Overview of Contents

## Examples
The quickest way to see how our implementation of the Hough Transform works is to view HoughPost_example.pdf for a visual walkthrough of the functions. Download HoughPost_example.Rmd to try it out yourself.

## The HoughPost R Package
To download our implementation, ensure you have the `devtools` package installed and loaded, and run: `install_github("ChenPanxi/Statistical_Computing/HoughPost")`
Functions include:
- `simulator`: Randomly generate points in Cartesian coordinates corresponding to either lines or circles, specifying a parameter that controls how "noisy" the points are.
- `hough_space`: Project points into Hough (parameter) space.
- `hough_trans`: Detect lines or circles and plot them on top of original data.

## Old Implementations
We went through several versions of the implementation, overhauling the code at each step for accuracy, efficiency, and style. See what didn't work out in the Old_Implementations folder.
