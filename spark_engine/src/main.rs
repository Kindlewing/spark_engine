use glium::glutin::{window::WindowBuilder, ContextBuilder};
use glium::glutin::event_loop::EventLoop;
use glium::Display;

mod core;

fn main() {
    let event_loop = EventLoop::new();
    let wb = WindowBuilder::new();
    let cb = ContextBuilder::new();
    let display = Display::new(wb, cb, &event_loop).unwrap();
    core::run(event_loop, display);
}
