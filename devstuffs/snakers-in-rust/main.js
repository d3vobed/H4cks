import init, { Game } from './pkg/snake_game.js';

async function run() {
    await init();
    
    const canvas = document.getElementById('gameCanvas');
    const ctx = canvas.getContext('2d');
    
    const game = new Game(canvas.width, canvas.height);
    
    document.addEventListener('keydown', (event) => {
        switch (event.key) {
            case 'ArrowUp':
                game.change_direction(0, -1);
                break;
            case 'ArrowDown':
                game.change_direction(0, 1);
                break;
            case 'ArrowLeft':
                game.change_direction(-1, 0);
                break;
            case 'ArrowRight':
                game.change_direction(1, 0);
                break;
        }
    });
    
    function render() {
        game.update();
        game.draw(ctx);
        requestAnimationFrame(render);
    }
    
    render();
}

run();
