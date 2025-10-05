def evaluate_postfix(expression):
    stack = []
    tokens = expression.split()
    for token in tokens:
        if token.isdigit():
            stack.append(int(token))
        else:
            operand2 = stack.pop()
            operand1 = stack.pop()
            if token == '+':
                result = operand1 + operand2
            elif token == '-':
                result = operand1 - operand2
            elif token == '*':
                result = operand1 * operand2
            elif token == '/':
                result = operand1 // operand2
            elif token == '^':
                result = operand1 ** operand2
            stack.append(result)
    return stack.pop()

if __name__ == '__main__':
    expression = input()
    result = evaluate_postfix(expression)
    print(result)