#Conway game of life using gganimate with ggwaffle

library(hrbrthemes)
library(waffle)
library(ggplot2)
library(tidyr)
library(tibble)
library(hrbrthemes)
library(dplyr)
library(gapminder)
library(gganimate)
library(Rcpp)
library(data.table)
library(magick)
library(purrr)

sourceCpp('GOLTools.cpp')
random_stateR <- function(dimx = 300, dimy = 300, threshold = .61)
{
  
  rand_state = matrix(nrow = dimx, ncol = dimy) %>% 
              apply(., 1, function(x) 
                x <- sample(c(0,1),
                            size = dimx,
                            replace = T,
                            prob = c(1-threshold, threshold)
                            )
                    )
  
  return(rand_state)
}

# returns 3x3 matrix of cell neighbors

build_history <- function(world = random_state(1280, 720, .43), epochs = 300){

  evolution <- vector(mode = "list", length = epochs)
  living <-  vector(mode = "list", length = epochs)
  for(i in 1:epochs)
  { 
    world <- toDF(evolve(world))
    evolution[[i]] <- world
    living[[i]] <- bodycount(DFtoNM(world))
    world <- DFtoNM(world)
  }
  return(list(Era = evolution, Population = unlist(living), Epoch = 1:epochs))
}
test <- build_history()
hm <- lapply(test$Era, function(x){
                          x %>% 
                      as_tibble() %>%
                      rowid_to_column(var="X") %>%
                      gather(key="Y", value="Z", -1) %>%
                      mutate(Y=as.numeric(gsub("V","",Y))) %>% 
                      as.data.table()
  
                                  }
            )

# png(file="example%02d.png", width=480, height=480)
# par(bg="#e6ffe6")

img <- image_graph(1280,720, res = 96,clip = F)

map(hm, function(x){
      p <- ggplot(x, aes(X, Y, fill= Z)) +
        geom_tile() +
        theme_void()+
        scale_fill_gradient(low="#ccb3ff", high = 'black')+
        theme(legend.position="none")+
        theme(rect = element_rect(fill = "transparent"))
      print(p)
                    },
    .progress = list(type = 'tasks',
                     format = "Rendering {cli::pb_bar} {cli::pb_current}/{cli::pb_total}",
                     clear = T
                    )
      )

dev.off()

animation <- image_animate(img, delay = 10, optimize = T)

image_write(animation, 
            paste0(c("GOLBig3",as.character(length(hm)),"d10.gif"), collapse = ""),
                    quality = 100)

# Use image magick
# system('"C:\\Program Files (x86)\\LyX 2.0\\imagemagick\\convert.exe" -delay 20  *.png animation.gif')
# Remove png files