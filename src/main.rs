use glium::glutin::event_loop::EventLoop;
use glium::glutin::{window::WindowBuilder, ContextBuilder};
use glium::Display;
use spark_engine::application::{run, Color};

fn main() {
    let event_loop = EventLoop::new();
    let wb = WindowBuilder::new();
    let cb = ContextBuilder::new();
    let display = Display::new(wb, cb, &event_loop).unwrap();
    let color = Color {
        red: 33.0 / 255.0,
        green: 33.0 / 255.0,
        blue: 33.0 / 255.0,
    };
    run(event_loop, display, color);
}
