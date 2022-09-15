use glium::{glutin, Surface};

pub struct Color {
    pub red: f32,
    pub green: f32,
    pub blue: f32
}

/// The main program loop
pub fn run(event_loop: glutin::event_loop::EventLoop<()>, display: glium::Display, color: Color) {
    event_loop.run(move |ev, _, control_flow| {
        let mut target = display.draw();
        target.clear_color(color.red,  color.green, color.blue, 1.0);
        target.finish().unwrap();

        let next_frame_time = std::time::Instant::now() +
            std::time::Duration::from_nanos(16_666_667);

        *control_flow = glutin::event_loop::ControlFlow::WaitUntil
            (next_frame_time);
        if let glutin::event::Event::WindowEvent { event, .. } = ev {
            if event == glutin::event::WindowEvent::CloseRequested {
                *control_flow = glutin::event_loop::ControlFlow::Exit; 
            }
        }
    });
}
