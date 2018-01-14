# Dokumentacja

## Specyfikacja projektu

### Cel

Celem projektu jest przede wszystkim poznanie konwolucyjnych sieci neuronowych, przestudiowanie zagadnień z nimi związanych oraz na podstawie zdobytej wiedzy - stworzenie własnej implementacji prostego systemu OCR ( ang. Optical Character Recognition ). Wszystkie elementy dotyczące istoty sieci konwolucyjnych ( ang. Convolutional Neural Networks – CNN ) będą tworzone przez nas samodzielnie w języku C.

Uwaga: Ze względu na założenia, napisany kod będzie znacznie wolniejszy od produkcyjnych biblotek. Nie służy on jednak jako produkt informatyczny, a jako narzędzie do nauki idei sieci CNN.

### Wejscie

Program na wejściu bedzie otrzymywał zdjęcie w postaci bitmapy.

### Działanie

Ze względu na dość powolne uczenie się sieci zrezygnowaliśmy z pierwotnej wersji projektu, zawężając alfabet do cyfr arabskich. Nie wpłynęło to na główny cel implementacyjny (samodzielne stworzenie bibliotek oraz przykładu sieci konwolucyjnej), a znacznie ułatwiło pracę nad kodem poprzez zmniejszenie ilości czasu potrzebnego na naukę sieci.

Obecnie sieć rozpoznaje przedstawioną na zdjęciu cyfrę.

### Wyjście

Wypisanie w konsoli cyfry, która znajduje się na wejściowym zdjeciu.

### Możliwe roszerzenia

* Obsługa zdjeć w różnych rozdzielczościach. (Biblioteka pozwala na realizację różnych rodzielczosci)
Zdjecia byłyby preprocesowane w celu przeskalowania zdjęcia do formatu, który przyjmuje na wejście CNN.
* Dodanie kolejnych znaków do alfabetu  
Dodanie liter alfabetu angielskiego. => Więcej wyjść w drugiej sięci neuronowej. => Dłuższy czas uczenia.
* Odczytywanie słów.  
Ze zdjecia zostaną wyizolowane i przekazane podstawowemu projektowi pojedyncze słowa. Na wyjściu zostanie wyświetlony odczytany tekst jako połaczenie słów odczytanych przez bazowy program. => Większy preprocesing i postprocesing. (Wymagane dodanie liter, patrz punkt wyżej)

## Plan projektu

Plan ma charakter orientacyjny i może być zmieniany w trakcie realizacji projektu.

1. Wiedza teoretyczna  
Zdobycie wiedzy teoretyczniej potrzebnej do implementacji projektu. w tym:
    1. Rozpoznanie i wybranie odpowiednich egzemplarzy wśród dostepnej literatury.
    2. Zapoznanie się z literaturą.
    3. Zdefiniowanie specyfikacji projektu na postawie zdobytej wiedzy.
2. Przygotowanie narzędzi  
Napisanie zestawu narzędzi:
   1. Bibloteka matematyczna
   2. Bibloteka CNN
   3. Bibloteka do parsowania plików graficznych ( IOlib )
   4. Generator danych testowych ( w języku python )
3. Realizacja CNN  
Stworzenie i wytrenowanie sieci, która rozpoznaje cyfrę podaną na zdjęciu.
6. Podsumowanie i wyciągnięcie wniosków  
Etap będzie polegał na krytycznym przyjrzeniu się projektowi i podsumowaniu jego przebiegu i wyników.

## Literatura
* [Convolutional Neural Networks for Visual Recognition](http://cs231n.github.io/) – kurs konwolucyjnej sieci neuronowej ze stanforda (głowne źródło wiedzy)
* „Deep Learning” – lan Goodfellow (książka zawierająca wiedzę teoretyczną)
* ["Machine Learning" by Andrew Ng](https://www.coursera.org/learn/machine-learning)

## Podsumowanie

# Mocne strony:
* został zrealizowany główny cel projketu - uczestniczenie w nim nauczyło nas zasad działania sieci konwolucyjnych
* projekt jest kompilowalny i działa poprawnie, sieć się uczy i rozpoznaje cyfry prawdopodobieństwiem z większym niż rozpoznawanie losowe
* realizacja postępowła zgodnie z planem, nie było znacznych opóźnień ani żadnych przerw w tworzeniu projektu

# Słabe strony:
* nauka sieci trwa bardzo długo, przez co byliśmy zmuszeni do okrojenia początkowo zakładanego alfabetu

# Wnioski:
* w przyszłosci warto byłoby usprawnić bibliotekę CNN poprzez wprowadzenie odpowiednich narzędzi:
** wątków
** bibliotek umożliwiających obliczenia na karcie graficznej
* sieci konwolucyjne pozwalają na rozpoznawanie obrazów z bardzo wysokim prawdopodobieństwem, jednakże wciąż jest ono zdecydowanie niższe niż możliwości ludzkiego mózgu

Jesteśmy bardzo zadowoleni z wyboru tematu projektu oraz przebiegu jego realizacji. Uwaźamy, że mimo pewnych przezkód, został zrealizowany adekwatnie do naszych możliwości. Dzięki niemu znacznie poszerzylismy swoją wiedzę i opanowaiśmy nowe dla nas narzedzie do informatycznej analizy obrazu.

