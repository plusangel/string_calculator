#include "simple_calc.h"

using namespace std::literals::string_literals;
using operand = std::variant<int, float>;
using elements = std::tuple<operand, operand, char>;

template <typename T> T functionality(T a, T b, char op) {
  T result{};
  switch (op) {
  case '+':
    result = a + b;
    break;
  case '-':
    result = a - b;
    break;
  case '*':
    result = a * b;
    break;
  case '/':
    if (b == 0)
      throw std::invalid_argument("division with 0");
    result = a / b;
    break;
  default:
    std::cout << "No valid operand" << std::endl;
  }
  return result;
}

elements identify_elements(const std::string &input) {
  auto found = input.find_first_of("+-*/"s);
  if (found == std::string::npos)
    throw std::invalid_argument("no operand symbol found");

  auto operand1 = std::string(input.begin(), input.begin() + found);
  auto operand2 = std::string(input.begin() + found + 1, input.end());
  char operation = input[found];

  try {
    if (operand1.find_first_of('.') == std::string::npos &&
        operand2.find_first_of('.') == std::string::npos) {
      return std::make_tuple(stoi(operand1), stoi(operand2), operation);
    } else {
      return std::make_tuple(stof(operand1), stof(operand2), operation);
    }
  } catch (const std::invalid_argument &e) {
    throw std::invalid_argument("no conversion could be performed");
  }
}

std::any calculator(const std::string &request) {
  std::any result;
  auto action_tuple = identify_elements(request);

  const auto opA = std::get<0>(action_tuple);
  const auto opB = std::get<1>(action_tuple);
  const auto op = std::get<2>(action_tuple);

  if (opA.index()) {
    result = functionality(std::get<float>(opA), std::get<float>(opB), op);
    // std::cout << std::any_cast<float>(result) << std::endl;
  } else {
    result = functionality(std::get<int>(opA), std::get<int>(opB), op);
    // std::cout << std::any_cast<int>(result) << std::endl;
  }

  return result;
}

/*int main() {
  try {
  //const auto str_add = "100-1"s;
  auto str_add = "100/0"s;
  const auto r = calculator(str_add);

  if (r.type() == typeid(int))
    std::cout << "the result is integer " << std::any_cast<int>(r) << std::endl;
  else
    std::cout << "the result is float " << std::any_cast<float>(r) << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what();
  } catch (const std::out_of_range &e) {
    std::cerr << "out of the range " << strerror(errno) << e.what();
  } catch (const std::exception &e) {
    std::cerr << "problem encountered: " << e.what();
  }

  return 0;
}*/
