simulator <- function(nshape=5, npoint=30, nnoise=100, p_min=-10, p_max=10, coef_min=-5, coef_max=5, radius=5,
                      noise_sd=0.1, slope_sd=1, shape_type='line',
                      point_size=1, point_width=2, point_shape=1, point_color='cornflowerblue',
                      line_noise=TRUE, noise=TRUE, show=TRUE, show_simulation=TRUE, noaxis=FALSE){

  x_coords_shape = c()
  y_coords_shape = c()

  x_center = c()
  y_center = c()
  r_circle = c()

  if(typeof(radius)=='double'){
    radius = c(radius, radius)
  }


  for(i in 1:nshape){

    # noise coefficient
    if(line_noise==TRUE){
      e = rnorm(npoint, mean=0, sd=noise_sd)
    } else if (line_noise==FALSE){
      e = 0
    }

    if(shape_type=='line'){

      x = runif(npoint, p_min, p_max)
      m = rnorm(1, mean=0, sd=slope_sd)
      b = runif(1, p_min, p_max)
      y = m*x + b + e

      x_coords_shape = c(x_coords_shape, x)
      y_coords_shape = c(y_coords_shape, y)

    } else if (shape_type=='circle') {
      s = runif(npoint, 0, 2*pi)
      r = runif(1, radius[1], radius[2])
      cx = runif(1, coef_min, coef_max)
      cy = runif(1, coef_min, coef_max)
      sinx = r*sin(s) + cx
      cosy = r*cos(s) + cy

      x_coords_shape = c(x_coords_shape, sinx)
      y_coords_shape = c(y_coords_shape, cosy)

      x_center = c(x_center, cx)
      y_center = c(y_center, cy)
      r_circle = c(r_circle, r)
    }
  }


  x_coords_noise = c()
  y_coords_noise = c()

  if(noise==FALSE | nnoise<=0){
    noises = data.frame()
  } else {
    random_x <- runif(nnoise, p_min, p_max)
    random_y <- runif(nnoise, p_min, p_max)

    x_coords_noise = c(x_coords_noise, random_x)
    y_coords_noise = c(y_coords_noise, random_y)
  }

  x_coords = c(x_coords_shape, x_coords_noise)
  y_coords = c(y_coords_shape, y_coords_noise)

  coord = data.frame(x=x_coords, y=y_coords)
  coord_shape = data.frame(x=x_coords_shape, y=y_coords_shape)
  coord_center = data.frame(x=x_center, y=y_center)

  if(show==TRUE && noaxis==TRUE){
    plot(coord$x, coord$y, axes=FALSE, xlab='', ylab='')
  } else {
    plot(coord$x, coord$y, xlab='x', ylab='y')
  }

  if(show==TRUE && show_simulation==TRUE){
    points(x_coords_shape, y_coords_shape, cex=point_size, lwd=point_width, pch=point_shape, col=point_color)
  }


  return(list(coord=coord, radius=r_circle, center=coord_center, coord_shape=coord_shape))
}
