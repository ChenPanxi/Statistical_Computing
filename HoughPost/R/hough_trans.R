hough_trans <- function(points, points_hs, points_shape=FALSE, steps=30, shape_type='line', radius=5, show=TRUE, show_simulation=FALSE){
  names(points) = c("x", "y")

  if(typeof(points_shape)!='logical'){show_simulation=TRUE}
  if(points_shape==FALSE && show_simulation==TRUE){print("Shape data is missing.")}

  if(shape_type=='circle'){

    x_df = expand.grid(x_center=points_hs$x, theta=seq(0, 2*pi, pi/steps))
    y_df = expand.grid(y_center=points_hs$y, theta=seq(0, 2*pi, pi/steps))
    xx = radius*sin(x_df$theta) + x_df$x_center
    yy = radius*cos(y_df$theta) + y_df$y_center
    params = data.frame(x=xx, y=yy)

    radius = matrix(radius, nr=1)
    radius = matrix(apply(radius, c(1, 2), function(a){rep(a,(nrow(points_hs)/length(radius)))}), nc=1)

    param_circle = data.frame(r=radius, x=points_hs$x, y=points_hs$y)

    draw_circle <- function(param){
      theta_seq = seq(0, 2*pi, pi/30)
      xx = param['r']*sin(theta_seq) + param['x']
      yy = param['r']*cos(theta_seq) + param['y']
      lines(xx, yy, lwd=3, xlim=c(-10, 10), ylim=c(-10, 10), col='red')
    }

    if(show==TRUE){
      plot(points$x, points$y, xlab='x', ylab='y')
      apply(param_circle, 1, FUN=draw_circle)
    }

  } else if (shape_type=='line'){
    x_coords = points_hs$x
    y_coords = points_hs$y

    slope = -cos(x_coords)/sin(x_coords)
    intercept = y_coords/sin(x_coords)

    params = data.frame(m=slope, b=intercept)

    if(show==TRUE){
      plot(points$x, points$y, xlab='x', ylab='y')
      apply(params, 1, function(a) {abline(a[2], a[1], lwd=3, col="red")})
    }

  }

  if(show==TRUE && show_simulation==TRUE){points(points_shape$x, points_shape$y, col='darkred')}


  return(params)

}
