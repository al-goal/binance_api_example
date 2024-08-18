# Binance API example

This application was created to fetch aggregated data from a Binance endpoint, split it into individual trades, and print these to the output.

# How to build and run

From the project root folder, run:

```console
foo@bar:~$ cmake -S . -B build
foo@bar:~$ cmake --build build
foo@bar:~$ ./build/src/binance_api_example <SYMBOL>
```

where <SYMBOL> is an actively traded symbol name. For testing, GUSDT was used.

# Rationale - data parsing

A straightforward solution to this problem would be in the form:

- Fetch data into a std::string object (e.g. using libcurl)
- Parse string into a JSON object tree, e.g. using the JSONCPP library, (https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)
- Traverse document tree; for each trade (an object inside the array) create a new JSON document and output it.

However, the overall format of the data and the emphasis on efficiency allow for a different approach. Inspired by SAX XML parsers, the data stream is processed character-by-character, and certain special characters, like brackets, colons or commans, trigger _events_ indicating that some part of the parsing was completed. For instance, a colon _:_ indicates that a _property name_ was completely received, whereas a closing curly bracket _}_  indicates that an object is finished.

An existing, full-fledged example of such an approach can be found under (https://json.nlohmann.me/features/parsing/sax_interface/) . In this implementation, the parser (class ``MiniJsonParser``) moves through the data stream and triggers some relevant events (defined in the ``ParseEventHandler`` interface class), such as:

- ``key()``: a property name has been completely received
- ``value()``: a property value has been completely received
- ``end_object()``: a complete JSON object has been received

A counterpart to the parser is the ``StreamEventHandler`` class, which stores the property names and values (i.e. the information of a single trade) and, once the object has been completely received, outputs the entire trade in the desired format. 

For the sake of efficiency and simplicity, the parser makes the following assumption about the input stream:

- It consists of a well-formed JSON document, consisting of one array of one or more JSON objects
- Each object contains a number of properties, but no sub-objects, arrays or any other construct
- There is no whitespace between a property name, the separating colon, and the corresponding value; likewise, no whitespace between successive objects.

These assumptions were empirically found to be true for the given API.

# API connection

Independent from the parsing classes mentioned above, some pieces of logic were implemented to handle the actual data fetching, making use of the libcurl library.

The ``process_url_to_stream()`` function takes an URL, an optional output stream (by default ``std::cout``) and an optional buffer flag (default ``false``). It sets up a curl object to parse the stream _as it is acquired_ (using the ``CURLOPT_WRITEFUNCTION`` option). Alternatively, it is possible to read the entire JSON document and parse it afterwards (buffer option ``true``).

# Dependencies

CMake, libcurl, googletest

# Requirements

Review the API of Binance USD(S)-M Futures that can be found in (https://binance-docs.github.io/apidocs/futures/en/#change-log). Then
- implement connectivity to the end-point GET /fapi/v1/aggTrades,
- receive a stream of trades. Write a parsing algorithm to parse the incoming stream of trades and print each trade in the form:
[

  {

    "a": 26129, // Aggregate tradeId

    "p": "0.01633102", // Price

    "q": "4.70443515", // Quantity

    "f": 27781, // First tradeId

    "l": 27781, // Last tradeId

    "T": 1498793709153, // Timestamp

    "m": true, // Was the buyer the maker?

  }

]
- measure the speed at which singular trades are parsed and comment on the algorithmic complexity of your parsing algorithm.