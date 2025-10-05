def parse_instruction_list(tokens):
    instructions = []
    i = 0
    while i < len(tokens):
        if tokens[i] == "CALL":
            instructions.append(("call", tokens[i+1]))
            i += 2
        else:
            instructions.append(("move", tokens[i]))
            i += 1
    return instructions

def main():
    import sys
    input = sys.stdin.readline

    n_funcs = int(input().strip())
    functions = {}
    for _ in range(n_funcs):
        line = input().strip()
        tokens = line.split()
        func_name = tokens[1]
        inst_tokens = tokens[2:]
        functions[func_name] = parse_instruction_list(inst_tokens)

    m = int(input().strip())
    main_tokens = input().strip().split()
    main_instructions = parse_instruction_list(main_tokens)

    pos = [0, 0]
    moves = {
        "U": (0, 1),
        "D": (0, -1),
        "L": (-1, 0),
        "R": (1, 0)
    }

    def execute_instructions(instructions, pos):
        for instr in instructions:
            if instr[0] == "move":
                dx, dy = moves[instr[1]]
                pos[0] += dx
                pos[1] += dy
            elif instr[0] == "call":
                execute_instructions(functions[instr[1]], pos)

    execute_instructions(main_instructions, pos)
    print(f"({pos[0]}, {pos[1]})")

if __name__ == "__main__":
    main()
