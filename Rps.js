
const startBtn = document.querySelector(".start");
const front = document.querySelector(".front");

const gameButtons = document.querySelector(".button-container");

const rock = document.querySelector(".rock");
const paper = document.querySelector(".paper");
const scissors = document.querySelector(".scissors");

const restart = document.querySelector(".restart");
const resultText = document.querySelector(".result");

let playerScore = 0;
let computerScore = 0;

startBtn.addEventListener("click", () => {
    front.classList.add("hidden");
    gameButtons.classList.remove("hidden");
})

function computerChoice() {
    const choices = ["rock", "paper", "scissors"];
    return choices[Math.floor(Math.random() * 3)];
}

function playRound(player) {
    
    const comp = computerChoice();
    let result;

    switch (`${player}-${comp}`) {

        case "rock-scissors":
        case "paper-rock":
        case "scissors-paper":
            result = "You Win";
            playerScore++;
        break;

         case "rock-paper":
        case "paper-scissors":
        case "scissors-rock":
            result = "You Lose";
            computerScore++;
        break;

        default:
            result = "draw";
    }
    resultText.textContent = 
    `You: ${player} | computer: ${comp} →${result};
    Score: You ${playerScore} ==>> ${computerScore} Computer`;
    

    gameButtons.classList.add("hidden");
    restart.classList.remove("hidden");
}

rock.addEventListener("click", () => playRound("rock"));
paper.addEventListener("click", () => playRound("paper"));
scissors.addEventListener("click", () => playRound("scissors"));

document.querySelector(".Y").addEventListener("click", () => {

    restart.classList.add("hidden");
    gameButtons.classList.remove("hidden");
    resultText.textContent = "";
});




/* console.log("===================================")
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
*/
