# SCOTR
Simple Convolutional neural network Optical Text Recognition

Created by Anna Bukowska, Radomir Krawczykiewicz

## Cel

Celem projektu jest zdobycie wiedzy o działaniu konwolucyjnych sieci neuronowych i na tej podstawie - stworznie własnej implementacji prostego systemu OCR (ang. Optical Character Recognition). Dążymy do tego, by program był w stanie analizować zdjęcia wydrukowanych tekstów i odczytywać zawarty na nich napis. Naszym głównym zródłem informacji będzie [kurs stanforda](http://cs231n.github.io/), na podstawie którego będziemy chcieli stworzyć naiwną implementację sieci konwolucyjnej (ang. Convolutional Neural Networks – CNN) w języku C. Ze względu na założenia, napisany kod będzie wolniejszy od produkcyjnych biblotek, jednak nauczy nas zasady działania sięci CNN.

### Wejscie

Zdjęcia będą przyjmowane w postaci bitmap.

### Działanie

Ze zdjecia zostaną wyizolowane i przekazane pierwszej sieci nauronowej pojedyncze słowa. Powinna być ona wstanie podać ich długość. Następnie druga sieć neuronowa na wejście będzie dostawać fragment obrazka przedstawiajacy pojedyncze słowo oraz w pętli – kolejne pozycje liter (aż do limitu podanego przez pierwszą sieć neuronową. Jej zadaniem będzie zwracanie poszczególnych liter. Na koniec program połączy otrzymane znaki w wyrazy i wyświetli użytkownikowi odczytany tekst.

### Wyjście

Plik zawierający pełne zdania.

## Plan projektu

* Wiedza teoretyczna  
Zdobycie wiedzy teoretyczniej potrzebnej do implementacji projektu. W tym:
    * Rozpoznanie i wybranie odpowiednich egzemplarzy wśród dostepnej literatury
    * Zapoznanie się z literaturą.
    * Wymyślenie modelu na postawie zdobytej wiedzy
* Przygotowanie srodowiska 
Napisaniu zestawu funkcji potrzebnych do implementacji sieci neuronowej. W tym do otworzenia plików graficznych w kodzie C oraz podstawowych operacji na macierzach:
    * Stworzenie biblioteki potrzebnej w realizacji projektu
    * Przygotowanie algorytmu generującego bitmapy słów, które posłużą do uczenia sieci
* Implementacja pierwszej CNN  
Stworzenie prostej sieci, która rozpoznaje liczbę znaków podaną na zdjęciu.
    * Rozpoznawanie ilości znaków w słowie.
* Implementacja drugiej (głównej) CNN
    * Stworzenie sieci, która jest wstanie podać znak na podstawie bitmapy słowa i jego pozycji w tym słowie.
* Dopracowywanie projektu
Etap będzie polegał na dodaniu jakiejś ciekawej funkcjonalności: rozpoznawania różnych czcionek lub rozszerzenie o znaki interpunkcyne 	lub zwiększenie domyślnej maksymalnej długości słowa z 10 do np. 20

## Literatura
* [Convolutional Neural Networks for Visual Recognition](http://cs231n.github.io/) – kurs konwolucyjnej sieci neuronowej ze stanforda (głowne źródło wiedzy)
* „Deep Learning” – lan Goodfellow (książka zawierająca wiedzę teoretyczną)
* ["Machine Learning" by Andrew Ng](https://www.coursera.org/learn/machine-learning)

## Model

Model bedzie postaci:
```
INPUT -> [[CONV -> RELU]*N -> POOL?]*M -> FC -> OUT | N,M >= 0
```

Ponieważ nasza sięc neuronowa bedzie się stosunkowo długo uczyć zastosujemy najprawdopodobniej jedna z możliwości:
* N = M = 1
* N = 2, M = 1
* N = 1, M = 2
    
## Bibloteka

Bibloteka bedzie napisana w jezyku C bez użycia biblotek, aby program był łatwo przenaszalny miedzy platformami.

Bibloteka bedzie zawierać następujące "klasy"(struktury w c wraz z funkcjami na nich operujacych):

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
        * Tensor<float> input;
        * Tensor<float> expected;
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
        * Tensor<float> back;
        * Tensor<float> in;
        * Tensor<float> out;
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
