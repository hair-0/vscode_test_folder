sentence = input()
words = sentence.split()
palindrome_count = sum(1 for word in words if word == word[::-1])
print(palindrome_count)
