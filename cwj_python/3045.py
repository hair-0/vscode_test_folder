def solve():
    morse_code_dict = {
        ".-": "A", "-...": "B", "-.-.": "C", "-..": "D", ".": "E",
        "..-.": "F", "--.": "G", "....": "H", "..": "I", ".---": "J",
        "-.-": "K", ".-..": "L", "--": "M", "-.": "N", "---": "O",
        ".--.": "P", "--.-": "Q", ".-.": "R", "...": "S", "-": "T",
        "..-": "U", "...-": "V", ".--": "W", "-..-": "X", "-.--": "Y",
        "--..": "Z"
    }

    morse_input = input()
    morse_words = morse_input.split("  ") 
    english_words = []

    for morse_word in morse_words:
        morse_letters = morse_word.split(" ") 
        english_word = ""
        for morse_letter in morse_letters:
            if morse_letter in morse_code_dict:
                english_word += morse_code_dict[morse_letter]
        english_words.append(english_word)

    output_sentence = " ".join(english_words)
    print(output_sentence)

solve()