import time
import subprocess
import eel


eel.init(".")

@eel.expose
def run_algorithm(algorithm, data):
    """
    This method exposes the C++ program to the HTML-JS-CSS Interface by passing the returning values of AI.exe.

    :param algorithm: The algorithm to be run. e.g DFS.
    :param data: the 9 tales without spaces e.g "123456789" is the solution.
    :return: The answer in a string in the protocol format. (protocol can be found on API.h)
    """

    # Pass the data and the instruction
    with open("data.txt", "w") as f:
        f.write(data)
    with open("instruction.txt", "w") as f:
        f.write("run_" + algorithm.lower())

    # Run the program
    subprocess.Popen(['AI.exe'], shell=True, creationflags=subprocess.SW_HIDE)

    # Wait for the result
    got_result = False
    while not got_result:
        with open("data.txt", "r") as f:
            result = f.read()
            if result != data:
                got_result = True
        time.sleep(0.1)
    return result


eel.start("pages/index.html")
