use glium::glutin::event_loop::EventLoop;
use glium::glutin::{window::WindowBuilder, ContextBuilder};
use glium::Display;
use spark_engine::application;

fn main() { let event_loop = EventLoop::new();
    let wb = WindowBuilder::new(); let cb = ContextBuilder::new();
    let display = Display::new(wb, cb, &event_loop).unwrap();
    application::run(event_loop, display);
}
