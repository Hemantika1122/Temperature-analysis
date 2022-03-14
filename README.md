# Temperature Analysis

A collection of C++ exercises for temperature data analysis, including numerical methods and data processing.

## Exercises

### 1. Bisection Method (`bisection_method.cpp`)
Finds zeros of a function using the bisection numerical method. Uses `f(x) = sin(x²)` as the test function. The user inputs the interval bounds [a, b] and tolerance value interactively.

**Features:**
- Interactive input for tolerance, initial and final points
- Validates that a root exists in the given interval
- Returns the root, function value at root, and iteration count
- Maximum 1000 iterations to prevent infinite loops

### 2. Lagrange Interpolation (`lagrange_interpolation.cpp`)
Generates N new (x, y) points using Lagrange polynomial interpolation from a precalculated dataset.

**Features:**
- User-specified number of interpolation points
- Uses `f(x) = sin(x²)` as the input function
- Generates evenly distributed interpolation points
- Outputs results to CSV file

### 3. Temperature CSV Converter (`temperature_csv_converter.cpp`)
Converts temperature data from tab-separated format to CSV with Julian dates.

**Input format:** `dd-mm-yyyy \t MaxT \t MinT`

**Output format:** `day;month;year;JulianDay;MaxTemp;MinTemp`

**Features:**
- Calculates Julian day from Gregorian date
- Adds blank line between different years
- Single header line in output

### 4. Daily Meteo Event (`daily_meteo_event.cpp`)
A C++ class for handling daily meteorological data with analysis capabilities.

**Features:**
- `DailyMeteoEvent` class with getters and setters
- Calculate mean temperature for any date
- Analyze yearly absolute max/min temperatures
- Calculate monthly average temperatures
- Find monthly absolute max/min temperatures
- Outputs results to text files

## Building

```bash
g++ -o bisection_method bisection_method.cpp -lm
g++ -o lagrange_interpolation lagrange_interpolation.cpp -lm
g++ -o temperature_csv_converter temperature_csv_converter.cpp -lm
g++ -o daily_meteo_event daily_meteo_event.cpp -lm
```

## Usage

### Bisection Method
```
Enter tolerance value
Enter initial point (a)
Enter final point (b)
```

### Lagrange Interpolation
```
Enter value for N (number of points to interpolate)
```

### CSV Converter & Meteo Event
Ensure input files (`data.txt`, `input_for_ans4.txt`) are in the working directory.

## Data Files

- `SevilleTemp1960-2020.txt` - Raw temperature data for Seville (1960-2020)
- `input_for_ans4.txt` - Processed data in CSV format for exercise 4
