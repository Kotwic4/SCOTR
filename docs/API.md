# API

### Matematyczna

* Vector<T>  
tablica jednowymiarowa o zmienym rozmiarze
    * pola
        * T * data
        * int size
    * metody
        * Vector( int _size )
        * void push_back( T x )
        * T& operator()( int i )
        * T& get( int i )
        * ~Vector()
* Point
    * pola
        * int x
        * int y
        * int z
    * metody
        * Point( int x, int y, int z )
* Tensor<T>  
3 wymiarowy zbiór danych
    * pola
        * T* data
        * Tsize size
    * metody
        * Tensor( int x, int y, int z )
        * Tensor( const Tensor& other )
        * Tensor<T> operator+( const Tensor<T>& other )
        * Tensor<T> operator-( const Tensor<T>& other )
        * T& operator()( int x, int y, int z )
        * T& operator()( Point i )
        * T& get( int x, int y, int z )
        * T& get( Point i )
        * ~Tensor()
* TestCase
    * pola
        * Tensor<float> input
        * Tensor<float> expected
   
### CNN

* Cnn  
Główna klasa bibloteki. Odpowiada za symulacje całej sieci neuronowej.
    * pola
        * Vector<Layer> layers
        * Point in_size
    * metody
        * Cnn( Point in_size )
        * void train( Tensor<float>& input, Tensor<float>& expected )
        * void train( Tensor<TestCase>& cases )
        * Tensor<float> forward( Tensor<float>& input )
        * void activate( Layer* layer, Tensor<float>& in )
        * void back_prop( Layer* layer, Tensor<float>& next_layer_back )
        * void addConvLayer( int stride, int spatial_extent, int number_filters, int padding )
        * void addFcLayer( int out_size )
        * void addPoolLayer( int stride, int spatial_extent )
        * void addReluLayer()
* Layer  
Struktura "abstrakcyjna" opisująca warstwe sieci neuronowej.
    * pola:
        * LayerType type
        * Tensor<float> back
        * Tensor<float> in
        * Tensor<float> out
* LayerType  
enum o wartosciach:
    * conv
    * fc
    * relu
    * pool
* ConvLayer
    * pola:
        * Layerype type = Layerype::conv
        * Tensor<float> back
        * Tensor<float> in
        * Tensor<float> out
        * Vector<Tensor<float>> filters
        * int stride
        * int spatial_extent
        * int padding
    * metody:
        * ConvLayer( int stride, int spatial_extent, int number_filters, int padding , Point in_size )
        * void activate( Tensor<float>& in )
        * void activate()
        * void back_prop( Tensor<float>& next_layer_back )
* FcLayer
    * pola:
        * Layerype type = Layerype::fc
        * Tensor<float> back
        * Tensor<float> in
        * Tensor<float> out
        * Vector<Tensor<float>> filters
        * Tensor<float> weights;
    * metody:
        * FcLayer( Point in_size, int out_size )
        * void activate( Tensor<float>& in )
        * void activate()
        * void back_prop( Tensor<float>& next_layer_back )
* PoolLayer  
    * pola:
        * Layerype type = Layerype::pool
        * Tensor<float> back
        * Tensor<float> in
        * Tensor<float> out
        * int stride
        * int spatial_extent
    * metody:
        * PoolLayer( int stride, int spatial_extent, Point in_size )
        * void activate( Tensor<float>& in )
        * void activate()
        * void back_prop( Tensor<float>& next_layer_back )
* ReluLayer
    * pola:
        * Layerype type = Layerype::relu
        * Tensor<float> back
        * Tensor<float> in
        * Tensor<float> out
        * Vector<Tensor<float>> filters
        * int stride
        * int spatial_extent
        * int padding
    * metody:
        * ReluLayer( Point in_size )
        * void activate( Tensor<float>& in )
        * void activate()
        * void back_prop( Tensor<float>& next_layer_back )
