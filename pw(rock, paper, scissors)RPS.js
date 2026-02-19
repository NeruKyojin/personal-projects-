console.log("===================================")
console.log("        Rock paper scissors")
console.log("===================================")

let roundsplayed = 0;
let result;
let hs = 0;
let cs = 0;
while (roundsplayed < 5) {

    const pc = prompt("Rock, Paper or Scissors: ").toLowerCase();

    const choices = ["rock", "paper", "scissors"];
    const compchoice = choices[Math.floor(Math.random() * 3)];
    
    
    switch (`${pc}-${compchoice}`) {
        case "rock-scissors":
        case "paper-rock":
        case "scissors-paper":
            result = "win";
            hs++;
        break;

        case "rock-paper":
        case "paper-scissors":
        case "scissors-rock":
            result = "lose";
            cs++;
        break;

    default:
        result = "draw";
    }

    roundsplayed++;

    console.log("the computer chose", compchoice)
    console.log("you", result)
}
console.log("Final Score -> H",hs," Computer:", cs);
