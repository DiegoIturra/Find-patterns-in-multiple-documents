import sys

def main():

    ## n of arguments
    n = len(sys.argv)

    ## if no arguments
    if n == 1:
        print("No arguments given")
        return

    docs = []
    for i in range(1, n):
        docs.append(sys.argv[i])

    finalText = ""


    for doc in docs:
        with open(doc, "r") as f:
            finalText += f.read()
        finalText += "$"

    # remove last $
    finalText = finalText[:-1]

    with open("finalText.txt", "w") as f:
        f.write(finalText)


if __name__ == "__main__":
    main()
