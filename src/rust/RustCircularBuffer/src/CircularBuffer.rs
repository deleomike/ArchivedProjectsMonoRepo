use std::fmt::format;

struct CircularBuffer {
    length: u64,
    average: f32,
    list: Vec<f32>
}

// Could be made more efficient through a smart averaging scheme. Not that it needs to be faster
impl CircularBuffer {
    // `Self` is the implementor type: `Sheep`.
    fn new(length: u64) -> CircularBuffer {

        CircularBuffer { length: length, list: [].to_vec(), average: 0.0 }
    }

    pub fn print(&self) {
        let mut printout = "[".to_string();

        for value in self.list.iter() {
            printout = format!("{0}, {1}", printout, value);
        }

        printout = format!("{0}]", printout);

        println!("{}", printout);
    }

    pub fn add(&mut self, value: f32) {

        if self.length <= self.list.len() as u64 && self.list.len() > 0{
            // Remove the first element
            println!("Remove");
            self.list.remove(0);
        }

        self.list.push(value);

        self.update_average();
    }

    pub fn average(&self) -> f32 {
        return self.average;
    }

    fn update_average(&mut self) {
        // Sum the vector
        let total: f32 = self.list.iter().sum();
        // Average
        self.average = total as f32 / self.list.len() as f32;
    }
}

fn main() {
    let mut buffer = CircularBuffer::new(1 as u64);

    buffer.add(5.0);
    buffer.add(10.0);

    buffer.print();

    println!("{0}", buffer.average())
}