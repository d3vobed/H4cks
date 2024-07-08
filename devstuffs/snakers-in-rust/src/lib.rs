use wasm_bindgen::prelude::*;
use web_sys::CanvasRenderingContext2d;

#[wasm_bindgen]
extern "C" {
    fn alert(s: &str);
}

#[wasm_bindgen]
pub struct Game {
    width: u32,
    height: u32,
    snake: Vec<(i32, i32)>,
    food: (i32, i32),
    direction: (i32, i32),
}

#[wasm_bindgen]
impl Game {
    pub fn new(width: u32, height: u32) -> Game {
        let snake = vec![(width as i32 / 2, height as i32 / 2)];
        let food = ((width / 4) as i32, (height / 4) as i32);
        let direction = (1, 0);
        Game {
            width,
            height,
            snake,
            food,
            direction,
        }
    }

    pub fn update(&mut self) {
        let mut new_head = (
            self.snake[0].0 + self.direction.0,
            self.snake[0].1 + self.direction.1,
        );

        if new_head.0 < 0 {
            new_head.0 = self.width as i32 - 1;
        } else if new_head.0 >= self.width as i32 {
            new_head.0 = 0;
        }

        if new_head.1 < 0 {
            new_head.1 = self.height as i32 - 1;
        } else if new_head.1 >= self.height as i32 {
            new_head.1 = 0;
        }

        if new_head == self.food {
            self.food = (
                (js_sys::Math::random() * self.width as f64) as i32,
                (js_sys::Math::random() * self.height as f64) as i32,
            );
        } else {
            self.snake.pop();
        }

        if self.snake.contains(&new_head) {
            self.snake = vec![(self.width as i32 / 2, self.height as i32 / 2)];
            self.direction = (1, 0);
            alert("Game Over!");
        } else {
            self.snake.insert(0, new_head);
        }
    }

    pub fn change_direction(&mut self, x: i32, y: i32) {
        self.direction = (x, y);
    }

    pub fn draw(&self, ctx: &CanvasRenderingContext2d) {
        ctx.clear_rect(0.0, 0.0, self.width as f64, self.height as f64);
        ctx.set_fill_style(&JsValue::from_str("green"));
        for (x, y) in &self.snake {
            ctx.fill_rect(*x as f64, *y as f64, 1.0, 1.0);
        }
        ctx.set_fill_style(&JsValue::from_str("red"));
        ctx.fill_rect(self.food.0 as f64, self.food.1 as f64, 1.0, 1.0);
    }
}
