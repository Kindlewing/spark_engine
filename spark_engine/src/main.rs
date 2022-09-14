use glium::glutin;

mod core;

fn main() {
    let event_loop = glutin::event_loop::EventLoop::new();
    let wb = glutin::window::WindowBuilder::new();
    let cb = glutin::ContextBuilder::new();
    let display = match glium::Display::new(wb, cb, &event_loop) {
        Ok(result) => result,
        Err(why) => println!("Could not get display: {}", why)
    };
    
    core::run(event_loop, display);
}
