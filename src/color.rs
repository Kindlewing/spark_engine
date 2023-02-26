/// Represents an RGB color
pub struct Color {
    pub r: f32,
    pub g: f32,
    pub b: f32,
}

impl Color {
    pub fn new(red: f32, green: f32, blue: f32) -> Self {
        Color {
            r: red / 255.,
            g: green / 255.,
            b: blue / 255.,
        }
    }
}
