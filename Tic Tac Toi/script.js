// Variables to hold the game state
let currentPlayer = 'X';
let gameBoard = ['', '', '', '', '', '', '', '', ''];
let gameActive = true;

// Select elements
const cells = document.querySelectorAll('.cell');
const statusDiv = document.getElementById('status');
const resetButton = document.getElementById('reset');

// Function to handle cell clicks
function handleCellClick(event) {
    const cellIndex = event.target.getAttribute('data-cell');
    
    if (gameBoard[cellIndex] || !gameActive) return;  // Ignore if the cell is already taken or the game is over
    
    // Mark the cell with the current player's symbol
    gameBoard[cellIndex] = currentPlayer;
    event.target.textContent = currentPlayer;
    event.target.classList.add('taken');
    
    // Check for a winner or draw
    if (checkWinner()) {
        statusDiv.textContent = `${currentPlayer} wins!`;
        gameActive = false;
        return;
    } else if (gameBoard.every(cell => cell)) {
        statusDiv.textContent = "It's a draw!";
        gameActive = false;
        return;
    }
    
    // Switch to the next player
    currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
    statusDiv.textContent = `Player ${currentPlayer}'s turn`;
}

// Function to check for a winner
function checkWinner() {
    const winPatterns = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8], // Rows
        [0, 3, 6], [1, 4, 7], [2, 5, 8], // Columns
        [0, 4, 8], [2, 4, 6] // Diagonals
    ];
    
    return winPatterns.some(pattern => {
        const [a, b, c] = pattern;
        return gameBoard[a] && gameBoard[a] === gameBoard[b] && gameBoard[a] === gameBoard[c];
    });
}

// Reset the game
function resetGame() {
    gameBoard = ['', '', '', '', '', '', '', '', ''];
    currentPlayer = 'X';
    gameActive = true;
    cells.forEach(cell => {
        cell.textContent = '';
        cell.classList.remove('taken');
    });
    statusDiv.textContent = `Player ${currentPlayer}'s turn`;
}

// Attach event listeners
cells.forEach(cell => cell.addEventListener('click', handleCellClick));
resetButton.addEventListener('click', resetGame);

// Initial game status
statusDiv.textContent = `Player ${currentPlayer}'s turn`;
