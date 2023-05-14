#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace py = pybind11;

py::list transform_row(const std::vector<std::string>& row, const py::list& transforms);

void trim(std::string& str) {
    // Find the position of the first non-whitespace character
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        // If the string is all whitespace, return an empty string
        str.clear();
        return;
    }

    // Find the position of the last non-whitespace character
    size_t last = str.find_last_not_of(' ');

    // Change the string in place to avoid unnecessary memory allocations
    str = str.substr(first, last - first + 1);
}

py::list parseCSV(const std::string& filePath, const py::kwargs& kwargs) {
    // Parse the optional arguments
    char delimiter = ',';
    bool skipHeader = false;
    bool trimSpace = true;
    py::list transforms = py::list();

    if (kwargs) {
        if (kwargs.contains("delimiter"))
            delimiter = kwargs["delimiter"].cast<char>();
        if (kwargs.contains("skip_header"))
            skipHeader = kwargs["skip_header"].cast<bool>();
        if (kwargs.contains("transforms"))
            transforms = kwargs["transforms"].cast<py::list>();
        if (kwargs.contains("trim"))
            trimSpace = kwargs["trim"].cast<bool>();
    }

    // Initialize a python list to return.
    py::list data;
    std::ifstream file(filePath);
    std::string line;
    bool transformRows = !transforms.empty();
    int n = 0;

    if (!file) {
        file.close();
        throw std::runtime_error("Failed to open the file: " + filePath);
    }

    // Skip the header row if specified
    if (skipHeader) {
        std::getline(file, line);
    }

    while (std::getline(file, line)) {
        ++n;

        std::vector<std::string>
            row;
        std::stringstream lineStream(line);
        std::string cell;
        bool insideQuotedField = false;

        // TODO: handle the case of a comma in middle of quoted cell
        // E.g "New York City, USA", 12345, "2023"
        // This should generate 3 columns not 4.
        while (std::getline(lineStream, cell, delimiter)) {
            if (!insideQuotedField && !cell.empty() && cell[0] == '"') {
                // Start of quoted field
                insideQuotedField = true;
                cell = cell.substr(1);  // Remove the leading quote
            }

            if (insideQuotedField && !cell.empty() && cell[cell.length() - 1] == '"') {
                // End of quoted field
                insideQuotedField = false;
                cell = cell.substr(0, cell.length() - 1);  // Remove the trailing quote
            }

            // Trim whitespace if neccessary.
            if (trimSpace) {
                trim(cell);
            }

            row.push_back(cell);
        }

        if (!skipHeader && n == 1) {
            data.append(row);
            continue;
        }

        // if transforms are provided, tranform row and append it to data
        if (transformRows) {
            data.append(transform_row(row, transforms));
        } else {
            data.append(row);
        }
    }

    file.close();
    return data;
}

py::list transform_row(const std::vector<std::string>& row, const py::list& transforms) {
    py::list transformedRow;
    for (size_t i = 0; i < row.size(); ++i) {
        const auto& cell = row[i];
        if (i < transforms.size() && !transforms[i].is_none()) {
            // Apply the transform function if available
            py::function transformFunc = transforms[i].cast<py::function>();
            py::object result = transformFunc(py::str(cell));
            transformedRow.append(result);
        } else {
            // No transform specified, keep the original value
            transformedRow.append(py::str(cell));
        }
    }
    return transformedRow;
}

PYBIND11_MODULE(csvparser, m) {
    m.doc() = "CSV Parser implemented in C++";

    m.def(
        "parse_csv", &parseCSV,
        R"pbdoc(
         Parse a CSV file and return a list of rows.

         Args:
             file_path (str): Path to the CSV file.
         kwargs:
             delimiter (str, optional): CSV column delimiter character. Default is ','.
             skip_header (bool, optional): Whether to skip the header row. Default is False.
             trim (bool, optional): Whether to trim whitespace around each cell . Default is True.
             transforms (List[Callable] or None, optional): A list of transform functions to apply to each column. Default is None.

         Returns:
             List[List[Any]]: Parsed CSV data.
         )pbdoc");
}
