# 8-puzzle-solver

<h1> What is it!? </h1>
<p> 
	8-puzzle-solver is a tool that uses the most famous euristic and non euristic AI algorithms to find a solution to the 8-puzzle problem. <br>
	It comes with a GUI that let's you enter your puzzle or generate a random one and select an algorithm of your choice to solve it. <br>
	It also desplays bentchmarks such as memory used for the frontier set or the CPU time it took to find the solution.
</p>

<h1> How it works?! </h1>
<p>
	The AI algorithms and the whole logic is implemented in C++. There's a Python program that exchanges data with that C++ program by writing/reading data to/from some common
	text files (sockets are too fancy :stuck_out_tongue_winking_eye:). <br> That Python script also hosts a little local web server by using a small library called <b> eel 	</b>.
	This web server of the Python script hosts a page that's actually the GUI to the C++ program (Electron is too fancy :stuck_out_tongue_winking_eye:). <br> So that's it! You've 	   learned every single detail!
	<p>
		<img src="readme/stacture.png">
	</p>
</p>
<h1> Screenshots </h1>
<p>
	<p> <img src="readme/screenshot_1.jpg"> </p>
	<p> <img src="readme/screenshot_2.jpg"> </p>
</p>
