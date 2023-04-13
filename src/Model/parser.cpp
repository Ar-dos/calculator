#include "parser.h"
namespace s21 {

void Calculator::Push(char c, int value) {
  bool flag = false;
  while (!flag) {
    if (characters.empty() || value > characters.top().value) {
      characters.push(Character(c, value));
      flag = true;
    } else {
      MoveFromCharactersToMain();
    }
  }
}

size_t Calculator::FindUnar(std::string arr, size_t i) {
  if (arr[i] == '-' && arr[i + 1] != ' ') {
    Push('~', 4);
    i++;
  } else if (arr[i] == '+' && arr[i + 1] != ' ') {
    i++;
  }
  return i;
}

size_t Calculator::FindValue(std::string arr, size_t i) {
  if (arr[i] >= '0' && arr[i] <= '9') {
    char* end = nullptr;
    double numbers = std::strtod(&arr[i], &end);
    i = end - &arr.front();
    if (std::isnan(numbers))
      main.push(Object(0.0));
    else
      main.push(Object(numbers));
  } else if (arr[i] == 'x') {
    main.push(*x);
    i++;
  } else if (!arr.compare(i, 3, "nan")) {
    main.push(NAN);
    i += 3;
  } else if (!arr.compare(i, 3, "inf")) {
    main.push(INFINITY);
    i += 3;
  }
  return i;
}

size_t Calculator::FindBrackets(std::string arr, size_t i) {
  if (arr[i] == '(') {
    characters.push(Character(arr[i], 1));
    i++;
  } else if (arr[i] == ')') {
    while (characters.top().symbol != '(') MoveFromCharactersToMain();
    characters.pop();
    i++;
  }
  return i;
}

size_t Calculator::FindBinarAndFunc(std::string arr, size_t i) {
  for (size_t j = 0; j < commands.size(); j++)
    if (!arr.compare(i, commands[j].input.length(), commands[j].input)) {
      Push(commands[j].symbol, commands[j].value);
      i += commands[j].length;
    }
  return i;
}

size_t Calculator::FindCommand(std::string arr, size_t i) {
  i = FindUnar(arr, i);
  i = FindValue(arr, i);
  i = FindBrackets(arr, i);
  i = FindBinarAndFunc(arr, i);
  return i;
}

void Calculator::Parse(std::string arr) {
  if (arr.length() > 255) throw std::invalid_argument("Input is too long.");
  for (size_t i = 0; i < arr.length();) i = FindCommand(arr, i);
  while (!characters.empty()) MoveFromCharactersToMain();
}

void Calculator::Reverse() {
  std::stack<Object> stack_temp;
  while (!main.empty()) stack_temp.push(GetObjectFromStack(&main));
  main = stack_temp;
}

Calculator::Object Calculator::GetObjectFromStack(std::stack<Object>* st) {
  Object res = st->top();
  st->pop();
  return res;
}

void Calculator::MoveFromCharactersToMain() {
  char temp = characters.top().symbol;
  characters.pop();
  main.push(Object(temp));
}

char Calculator::CheckZTop() {
  char res = '0';
  if (!main.empty()) res = main.top().symbol;
  return res;
}

int Calculator::CheckTypeTop() {
  int res = 0;
  if (!main.empty()) res = main.top().type;
  return res;
}

void Calculator::DoOperation(char c, std::stack<Object>* stack_temp) {
  if (c == '-') {
    main.pop();
    double v1 = GetObjectFromStack(stack_temp).data;
    double v2 = GetObjectFromStack(stack_temp).data;
    stack_temp->push(v2 - v1);
  } else if (c == '+') {
    main.pop();
    stack_temp->push(GetObjectFromStack(stack_temp).data +
                     GetObjectFromStack(stack_temp).data);
  } else if (c == '*') {
    main.pop();
    stack_temp->push(GetObjectFromStack(stack_temp).data *
                     GetObjectFromStack(stack_temp).data);
  } else if (c == '/') {
    main.pop();
    double v1 = GetObjectFromStack(stack_temp).data;
    double v2 = GetObjectFromStack(stack_temp).data;
    stack_temp->push(v2 / v1);
  } else if (c == '~') {
    main.pop();
    stack_temp->push(-1 * GetObjectFromStack(stack_temp).data);
  } else if (c == '!') {
    main.pop();
    stack_temp->push(sin(GetObjectFromStack(stack_temp).data));
  } else if (c == '@') {
    main.pop();
    stack_temp->push(cos(GetObjectFromStack(stack_temp).data));
  } else if (c == '#') {
    main.pop();
    stack_temp->push(tan(GetObjectFromStack(stack_temp).data));
  } else if (c == '$') {
    main.pop();
    stack_temp->push(sqrt(GetObjectFromStack(stack_temp).data));
  } else if (c == 's') {
    main.pop();
    stack_temp->push(asin(GetObjectFromStack(stack_temp).data));
  } else if (c == 'c') {
    main.pop();
    stack_temp->push(acos(GetObjectFromStack(stack_temp).data));
  } else if (c == 't') {
    main.pop();
    stack_temp->push(atan(GetObjectFromStack(stack_temp).data));
  } else if (c == '%') {
    main.pop();
    double v1 = GetObjectFromStack(stack_temp).data;
    double v2 = GetObjectFromStack(stack_temp).data;
    stack_temp->push(fmod(v2, v1));
  } else if (c == '&') {
    main.pop();
    stack_temp->push(log(GetObjectFromStack(stack_temp).data));
  } else if (c == '?') {
    main.pop();
    stack_temp->push(log10(GetObjectFromStack(stack_temp).data));
  } else if (c == '^') {
    main.pop();
    double v1 = GetObjectFromStack(stack_temp).data;
    double v2 = GetObjectFromStack(stack_temp).data;
    stack_temp->push(pow(v2, v1));
  }
}

double Calculator::Math() {
  std::stack<Object> stack_temp;
  while (!main.empty()) {
    if (CheckTypeTop() == kPointer) stack_temp.push(GetObjectFromStack(&main));
    if (CheckTypeTop() == kSymbol) DoOperation(CheckZTop(), &stack_temp);
    if (CheckTypeTop() == kNumber) stack_temp.push(GetObjectFromStack(&main));
  }
  return stack_temp.top().data;
}

double Calculator::DoCalculation(std::string input) {
  Calculator::Parse(input);
  Calculator::Reverse();
  return Math();
}
}  // namespace s21
