# Image processing library (ascii.PGM)

An image processing library that it's capable of applying brightness, gamma and image convulution (vertical/horizontal sobel, gaussian blur, mean blur) filters. It also has an image drawing module.


## Demo

### Demo bash script
```sh
./demo.sh
```
### Compile with C++

```sh
g++ -Iheaders ./src/*.cpp <yourfile>.cpp -o
```

### Gamma and Blur
![Image convulution 1](https://i.imgur.com/0x2B50n.png)

### Sobel filter for edge detection
![Sobel 1](https://i.imgur.com/uw8pO50.png)
