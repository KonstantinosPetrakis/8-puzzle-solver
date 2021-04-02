let space_location = 9;
let animation_speed = 500;
let puzzle = "123456789";
let movements;


/**
 * Moves a tale if possible to space.
 * @param id is the id of the tale that user wants to be moved to space.
 */
function move_to_space(id){
    id = id[1]; // Get only the digit
    let ids = {}
    ids[space_location - 3] = "up";
    ids[space_location + 3] = "down";
    ids[space_location - 1] = "left";
    ids[space_location + 1] = "right";

    if (ids[id]){
        space_move(ids[id]);
    }
}

/**
 * It moves the space to a direction.
 * @param direction the direction that space tale will be moved to ("up", "down", "left", "right").
 */
function space_move(direction){
    let reverse_move = {"up": "down", "down": "up", "left": "right", "right": "left"};
    //Check append/remove from movements to-do list
    if (movements) {
        if (direction === movements[0]) {
            movements.shift();
        }
        else {
            movements.unshift(reverse_move[direction]);
        }
        update_steps();
    }

    // Some dictionaries to define movement to ids and to CSS animation attributes
    let ids = {"up": -3, "down": 3, "left": -1, "right": 1};
    let attributes = {"up": "move-down", "down": "move-up", "left": "move-right", "right": "move-left"};
    let tale_to_be_moved = document.getElementById("t" + (space_location + ids[direction]).toString());
    let space_tale = document.getElementById("t" + space_location.toString());


    tale_to_be_moved.setAttribute(attributes[direction], "");
    tale_to_be_moved.style.zIndex = "1";
    space_location = parseInt(tale_to_be_moved.id[1]);

    // Function to be called after CSS animation is done in order to actually swap the tales (not only visually).
    setTimeout(() =>{
        tale_to_be_moved.style.zIndex = "0";
        // Swap text
        space_tale.innerText = tale_to_be_moved.innerText;
        tale_to_be_moved.innerText = "";
        // Swap space and onClick attribute
        tale_to_be_moved.setAttribute("space", "");
        tale_to_be_moved.removeAttribute("onClick");
        space_tale.setAttribute("onClick", "move_to_space(this.id)");
        space_tale.removeAttribute("space");

        tale_to_be_moved.removeAttribute(attributes[direction]);

        update_puzzle();
    }, animation_speed);
}

/**
 * Initializes the puzzle using the text input of HTML.
 */
function insert_puzzle(){
    let nums = document.getElementById("puzzle_input_text").value.split(" ");
    for (let i=0; i<9; i++){
        let tale = document.getElementById("t" + (i + 1).toString())
        tale.innerHTML = nums[i];

        if (tale.hasAttribute("space")){
            tale.removeAttribute("space");
        }
        if (!tale.hasAttribute("onClick")){
            tale.setAttribute("onClick", "move_to_space(this.id)");
        }

        if (nums[i] === "9"){
            tale.setAttribute("space", "");
            tale.innerHTML = "";
            space_location = i + 1;
            if (tale.hasAttribute("onClick")){
                tale.removeAttribute("onClick");
            }
        }
    }
    puzzle = nums.join("");
}

/**
 * This method generates a puzzle with the according difficulty entered by the user. NEEDS FIXING.
 */
function generate_puzzle(){
    // Find the value selected
    let radios = document.getElementsByName("radio");
    let value = 0;
    for (let i=0; i<radios.length; i++){
        if (radios[i].checked){
            value = parseInt(radios[i].value);
        }
    }

    // Do the loops for the value selected
    let reverse_move = {"up": "down", "down": "up", "left":"right", "right": "left"};
    let last_move = ""

    for (let i=0; i<value; i++) {
        setTimeout(function () {
            let available_choices = ["up", "down", "right", "left"];

            if (space_location < 4) {
                available_choices = available_choices.filter(item => item !== "up");
            }
            if (space_location > 6) {
                available_choices = available_choices.filter(item => item !== "down");
            }
            if (space_location % 3 === 1) {
                available_choices = available_choices.filter(item => item !== "left");
            }
            if (space_location % 3 === 0) {
                available_choices = available_choices.filter(item => item !== "right");
            }
            available_choices = available_choices.filter(item => item !== reverse_move[last_move]);

            let move = available_choices[Math.floor(Math.random() * available_choices.length)];
            space_move(move);
            last_move = move;
        }, i * animation_speed);
    }
}

/**
 * This method alters the animation speed of the tiles moving around.
 */
function alter_animation_speed(){
    animation_speed = parseInt(document.getElementById("animation_speed").value);
    let speed_in_s = (animation_speed / 1000.0).toString() + "s";

    let rules = document.styleSheets[0].cssRules;
    for (let i=0; i<rules.length; i++){
        if (rules[i].cssText.startsWith("#puzzle_container .tale[move-right]") ||
            rules[i].cssText.startsWith("#puzzle_container .tale[move-left]") ||
            rules[i].cssText.startsWith("#puzzle_container .tale[move-down]") ||
            rules[i].cssText.startsWith("#puzzle_container .tale[move-up]")){
                rules[i].style.transitionDuration = speed_in_s;
        }
    }
}

/**
 * This function updates the puzzle variable. Should be called everytime tales are moving around. So the call on API would work.
 */
function update_puzzle(){
    let str = "";
    let tales = document.getElementsByClassName("tale");
    for (let i=0; i<tales.length; i++){
        str += !tales[i].hasAttribute("space") ? tales[i].innerHTML : "9";
    }
    puzzle = str;
}

/**
 * This function runs the algorithm selected for the entered puzzle.
 */
async function run_algorithm() {
    let algorithm = document.getElementById("algorithm").value;
    let data = (await eel.run_algorithm(algorithm, puzzle)()).split(" ");

    let stats = data[0] + " finished in: " + data[1] + "s" + "<br>" +
        "Solution length: " + data[2] + "<br>" +
        "Max frontier size: " + data[3] + "<br>"+
        "States expanded: " + data[4];

    movements = data[5].split(",").filter(item => !["", " "].includes(item)); // Filter the trash.

    document.getElementById("stats_content").innerHTML = stats;
    update_steps();
}

/**
 * This function updates the steps div.
 */
function update_steps(){
    // Clear all the old steps
    while(document.getElementById("steps").childElementCount > 1){ //Leave the button
        document.getElementById("steps").removeChild(document.getElementById("steps").firstChild);
    }

    // Write the new steps
    if (movements) {
        if (movements.length < 100000){
            // Insert the new steps
            for (let i=movements.length - 1; i >= 0; i--) {
                let step = document.createElement("div");
                step.innerHTML = movements[i];
                document.getElementById("steps").insertBefore(step, document.getElementById("steps").firstChild);
            }
        }
        else{
            document.getElementById("steps").innerHTML = "Steps > 100.000. Impossible to follow.";
        }
    }

}

/**
 * This method solves the puzzle by following the movements that were given by some search algorithm.
 */
function follow_steps(){
    for (let i=0; i<movements.length; i++){
        if (movements[i] === "up" || movements[i] === "down" || movements[i] === "right" || movements[i] === "left") {
            setTimeout(space_move, (animation_speed * i), movements[i]);
        }
    }
}