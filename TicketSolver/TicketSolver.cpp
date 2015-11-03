#include <stdio.h>
#include <iterator>
#include <limits>

#include <math.h>
#include <time.h>
#include <errno.h>
#include "TicketSolver.h"

#if !defined(WIN32) && !defined(__WIN32__)
#define CLK_TCK CLOCKS_PER_SEC
#endif

const std::string TicketSolver::version = "1.0.0";
const std::string TicketSolver::description = "This program finds combination of operation signs and brackets between given digits to obtain the required expression result.";
const std::string TicketSolver::author = "Alexander Yampolsky. <yampa@yandex.ru> 2015 https://github.com/ayampolsky/TicketSolver";

const int TicketSolver::OperationPriorities [OPER_MAX] = {
  0, // OPER_ADD
  0, // OPER_SUB
  1, // OPER_DIV
  1, // OPER_MUL
  2, // OPER_POW
  3  // OPER_CAT
};

const char *TicketSolver::OperationNames [OPER_MAX] = {
  " + ",
  " - ",
  " / ",
  " * ",
  " ^ ",
  "_"};

#if defined(WIN32) || defined(__WIN32__)
int _matherr(struct _exception *e)
{
  e->retval = std::numeric_limits<double>::quiet_NaN();
  return 1;
}
#endif

static inline bool isnan_custom (const double f)
{
  const double double_max = std::numeric_limits<double>::max();
  const double double_min = -double_max;
  return (!((f <= double_max) && (f >= double_min)));
}

TicketSolver::TicketSolver () :
  useBrackets (true)
{
}

TicketSolver::~TicketSolver ()
{
}

std::list<int> TicketSolver::ConvertDigits (const std::string digits)
{
  std::list<int> numbers;

  for (size_t i = 0; i < digits.length (); i++) {
    numbers.push_back (digits [i] - 48);
  }
  return numbers;
}

const std::string TicketSolver::writeExpression ()
{
  char buffer [256];
  char *c = buffer;
  std::list<TicketOperation>::iterator op_it = operations.begin ();
  for (std::list<int>::iterator it = numbers.begin (); it != numbers.end (); it++, op_it++) {
    if (op_it != operations.begin ()) {
      for (int i = 0; i < op_it->closeBracket; i++) {
        c += sprintf (c, ")");
      }
      if (op_it != operations.end()--) {
        c += sprintf (c, "%s", OperationNames [op_it->operation]);
      }
    }
    for (int i = 0; i < op_it->openBracket; i++) {
      c += sprintf (c, "(");
    }
    c += sprintf (c, "%d", *it);
  }

  for (int i = 0; i < op_it->closeBracket; i++) {
    c += sprintf (c, ")");
  }

  std::string expression (buffer);
  return expression;
}

int TicketSolver::doOperation (std::list<int>::iterator max_it, std::list<TicketOperation>::iterator max_op_it)
{
  bool res = true;
  int b = *max_it; // Second value
  max_it--;
  int a = *max_it; // First value

  switch (max_op_it->operation) {
  case OPER_CAT :
    a = 10 * a + b;
    break;
  case OPER_ADD :
    a = a + b;
    break;
  case OPER_SUB :
    a = a - b;
    break;
  case OPER_MUL :
    a = a * b;
    break;
  case OPER_DIV :
    if (b && !(a % b)) {
      a = a / b;
    }
    else {
      res = false;
    }
    break;
  case OPER_POW : {
        const double f = pow (a, b);
        //if ((isnan_custom (f)) || (f != (int) f) || (errno == ERANGE) || (errno == EDOM)) {
        if ((isnan_custom (f)) || (f != (int) f)) {
          res = false;
        }
        else {
          a = f;
        }
      break;
    }
  default :
    res = false;
    break;
  }

  if (res) {
    // Store result
    *max_it = a;
  }
  return res;
}

int TicketSolver::iterateBrackets (const int targetResult, int &bracketsIterations, int &bracketsSolutions, const bool silent, const bool debug)
{
  // Iterate brackets sequencies and discard wrong expressions
  // 1. If there are too many brackets
  // 2. If number of brackets is negative
  // 3. If brackets don't match
  // 4. If brackets are around concatenation operation
  // 5. If there are double brackets around one expression

  const std::list<int> numbersBackup = numbers;
  const std::list<TicketOperation> operationsBackup = operations;
  const int digitsCount = numbers.size ();
  const int bracketsMax = (digitsCount - 1) / 2;
  const int iterationsCount = pow (2 * bracketsMax + 1, digitsCount);

  int res = 0;
  bool changed = false;
  int iterationCounter = 0;
  bool done = false;
  char buffer [16];

  bracketsIterations = 0;
  bracketsSolutions = 0;

  for (int bracketsMask = 0; bracketsMask < iterationsCount; bracketsMask++) {
    int sequence = bracketsMask;
    int bracketsAmount = 0;                 // Amount of brackets in expression
    int previousBrackets = 0;               // Number of previously added brackets

    if (changed) {                          // Restore numbers and operations after expression calculation
      numbers = numbersBackup;
      operations = operationsBackup;
      changed = false;
    }

    std::list<TicketOperation>::iterator op_it = operations.begin ();
    while (1) {
      // 0 - no brackets (solutions without brackets have greater priority)
      // 1 - bracketsMax - open brackets
      // bracketsMax + 1 - 2 * bracketsMax - close brackets
      const int brackets = sequence % (2 * bracketsMax + 1);

      if (brackets && (op_it->operation == OPER_CAT)) {
        break;                              // Ignore expressions with brackets around concatenation operation (4)
      }

      if ((brackets > 0) && (brackets <= bracketsMax)) {
        op_it->openBracket = brackets;      // Add open brackets
        bracketsAmount += brackets;
        previousBrackets = brackets;
        if (bracketsAmount > bracketsMax) { // Ignore expressions with too many brackets (1)
          break;
        }
      }
      else {
        op_it->openBracket = 0;             // Clear open brackets in current operation
      }

      op_it++;                              // Increase operation index

      if (op_it == operations.end ()) {
        break;
      }

      if (brackets && (op_it->operation == OPER_CAT)) {
        break;                              // Ignore expressions with brackets around concatenation operation (4)
      }

      if (brackets > bracketsMax) {
        op_it->closeBracket = brackets - bracketsMax; // Add close brackets
        bracketsAmount -= brackets - bracketsMax;
        if ((previousBrackets > 1) && (previousBrackets == (brackets - bracketsMax))) {
          break;                            // Ignore expressions with multiple closing brackets after the same number of open brackets (5)
        }
        if (bracketsAmount < 0) {           // Ignore expressions with negative amount of brackets (2)
          break;
        }
      }
      else {
        op_it->closeBracket = 0;            // Clear close brackets in current operation
      }

      sequence /= (2 * bracketsMax + 1);

      //sprintf (buffer, "\r\n%5d ", iterationCounter);
      //solution.append (buffer).append (writeExpression());
    }

    if (bracketsAmount || (op_it != operations.end ())) {
      continue;                             // Ignore expression with unmatching brackets or where not all operations were set (3)
    }

    if (!silent || done) {                  // Not silent mode or calculation of expression done
      solution.clear ();
      solution.append (writeExpression());
    }

    bracketsIterations++;
    iterationCounter++;
    if (!debug) {
      res = reduceList (numbers.begin (), numbers.end (), operations.begin (), operations.end (), silent && !done);
      changed = true;
      if (res && (numbers.size() == 1)) {
        if (!silent) {
          solution.append (" OK");
        }
        if (numbers.front() == targetResult) {
          if (silent && !done) {            // Restart expression calculation and print expression
            done = true;
            bracketsMask--;
            continue;
          }
          else {
            if (silent) {
              solution.append (" OK");
            }
          }
          solution.append (" Found!");
          bracketsSolutions++;
          log.push_back (solution);
          break;
        }
        else if (!silent) {
          log.push_back (solution);
        }
      }
      else {
        if (!silent) {
          solution.append (" Error!");
        }
      }
    }
    else {
      sprintf (buffer, "\r\n%5d ", iterationCounter);
      solution.append (buffer).append (writeExpression());
      log.push_back (solution);
    }
  }
  return true;
}

int TicketSolver::reduceList (std::list<int>::iterator number_begin, std::list<int>::iterator number_end, std::list<TicketOperation>::iterator op_begin, std::list<TicketOperation>::iterator op_end, const bool silent, const int level)
{
  bool res = true;
  bool changed = false;
  std::list<TicketOperation>::iterator op_it = op_begin;

  for (std::list<int>::iterator it = number_begin; it != number_end;) {
    if (!level || (it != number_begin)) { // Skip first number
      if (op_it->closeBracket) { // Limit calculation on closed bracket
        number_end = it;
        op_end = op_it;
        break;
      }
      if (op_it->openBracket) { // Call reduceList recursively for bracketed expression
        res = reduceList (it, number_end, op_it, op_end, silent, level + 1);
        if (!res) {
          return res;
        }
        continue;
      }
    }
    it++;
    op_it++;
  }

  if (op_it->closeBracket) { // Limit calculation on closed bracket
    //number_end = it;
    op_end = op_it;
    //break;
  }

  while (std::distance (number_begin, number_end) > 1) {
    std::list<int>::iterator max_it = number_begin;
    std::list<TicketOperation>::iterator max_op_it = op_begin;
    max_it++;
    max_op_it++;
    op_it = op_begin;

    for (std::list<int>::iterator it = number_begin; it != number_end; it++, op_it++) {
      if (it == number_begin) { // Skip first number
        continue;
      }
      if (OperationPriorities [op_it->operation] > OperationPriorities [max_op_it->operation]) {
        max_it = it;            // Store operation with maximum priority;
        max_op_it = op_it;
      }
      //if (OperationPriorities [max_op_it->operation] == OperationPriorities [OPER_MAX - 1]) {
      //  break;
      //}
    }
    res = doOperation (max_it, max_op_it);

    if (res) {
      // Remove number and operation
      numbers.erase (max_it);
      operations.erase (max_op_it);

      if (!silent) {
        if (std::distance (number_begin, number_end) > 1) {
          solution.append (" = ").append (writeExpression());
        }
      }
    }
    else {
      // Error (division by zero)
      if (!silent) {
        solution.append (" Error in expression");
      }
      break;
    }
    changed = true;
  }

  const bool finalBracket = ((op_end != operations.end ()) && op_end->closeBracket);

  if (op_begin->openBracket && finalBracket) {
    op_begin->openBracket--;
    op_end->closeBracket--;
  }
  else if (op_begin->openBracket || finalBracket) {
    if (!silent) {
      solution.append (" Brackets mistmatch");
    }
    res = false;
  }

  if ((!silent) && res && changed) {
    solution.append (" = ").append (writeExpression());
  }

  return res;
}

int TicketSolver::SolveSingle (const std::string digits, const int targetResult)
{
  bool res = false;
  numbers = ConvertDigits (digits);
  operations.clear ();
  log.clear ();

  TicketOperation ops [] = {
    {OPER_IDL, 0, 0},
    {OPER_MUL, 0, 0},
    {OPER_ADD, 0, 1},
    {OPER_POW, 0, 1},
    {OPER_MUL, 0, 0},
    {OPER_CAT, 0, 0},
    {OPER_IDL, 2, 0}
  };

  operations.push_back(ops [0]);
  operations.push_back(ops [1]);
  operations.push_back(ops [2]);
  operations.push_back(ops [3]);
  operations.push_back(ops [4]);
  operations.push_back(ops [5]);
  operations.push_back(ops [6]);

  int iterationsCalculated = 0;
  int solutionsCount = 0;

  solution.clear ();

  const clock_t startClock = clock ();

  if (useBrackets) {
    int bracketsIterations = 0;
    int bracketsSolutions = 0;
    res = iterateBrackets (targetResult, bracketsIterations, bracketsSolutions, false, false);
    iterationsCalculated += bracketsIterations;
    solutionsCount += bracketsSolutions;
  }
  else {
    solution.append (writeExpression());

    iterationsCalculated++;

    res = reduceList (numbers.begin (), numbers.end (), operations.begin (), operations.end (), false);

    if (res && (numbers.size() == 1)) {
      solution.append (" OK");
      if (numbers.front() == targetResult) {
        solution.append (" Found!");
        solutionsCount++;
      }
    }
    else {
      solution.append (" Error!");
    }

    log.push_back (solution);
  }

  const clock_t endClock = clock ();
  const float computationTime = (endClock - startClock) / CLK_TCK;

  char buffer [256];
  sprintf (buffer, "Done %d iterations in %.3f s, found %d solution(s).", iterationsCalculated, computationTime, solutionsCount);
  log.push_back (buffer);

  return res;
}

int TicketSolver::Solve (const std::string digits, const int targetResult)
{
  bool res = false;
  int solutionsCount = 0;
  int iterationsCalculated = 0;
  const std::list<int> numbersEntered = ConvertDigits (digits);
  operations.clear ();
  log.clear ();

  const int digitsCount = numbersEntered.size () - 1;
  const int iterationsCount = pow ((float) OPER_MAX, (float) digitsCount);

  const clock_t startClock = clock ();

  for (int operationsMask = 0; operationsMask < iterationsCount; operationsMask++) {
    numbers = numbersEntered;
    operations.clear ();
    int sequence = operationsMask;
    TicketOperation op = {OPER_IDL, 0, 0};
    operations.push_back (op);
    for (int i = 0; i < digitsCount; i++) {
      op.operation = (Operation) (sequence % OPER_MAX);
      operations.push_back (op);
      sequence /= OPER_MAX;
    }
    op.operation = OPER_IDL;
    op.closeBracket = 0;
    op.openBracket = 0;
    operations.push_back (op);

    //solution.clear ();
    if (useBrackets) {
      int bracketsIterations = 0;
      int bracketsSolutions = 0;
      res = iterateBrackets (targetResult, bracketsIterations, bracketsSolutions, true, false);
      iterationsCalculated += bracketsIterations;
      solutionsCount += bracketsSolutions;
    }
    else {
      solution.append (writeExpression());

      iterationsCalculated++;

      res = reduceList (numbers.begin (), numbers.end (), operations.begin (), operations.end (), false);

      bool saveSolution = false;
      if (res && (numbers.size() == 1)) {
        solution.append (" OK");
        if (numbers.front() == targetResult) {
          solution.append (" Found!");
          solutionsCount++;
          saveSolution = true;
        }
      }
      else {
        solution.append (" Error!");
      }

      if (saveSolution) {
        log.push_back (solution);
      }
    }
  }

  const clock_t endClock = clock ();
  const float computationTime = (endClock - startClock) / CLK_TCK;

  char buffer [256];
  sprintf (buffer, "Done %d iterations in %.3f s, found %d solution(s).", iterationsCalculated, computationTime, solutionsCount);
  log.push_back (buffer);

  return res;
}

void TicketSolver::getVersion (std::string &version, std::string &description, std::string &author)
{
  version = TicketSolver::version;
  description = TicketSolver::description;
  author = TicketSolver::author;
}
