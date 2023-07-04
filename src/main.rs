use std::{error::Error, time::Duration};
// use rppal::gpio::Gpio;
use rppal::pwm::{Channel, Pwm, Polarity};
use std::thread;

fn main() -> Result<(), Box<dyn Error>> {
    
    println!("Starting Program...");

    // let gpio = Gpio::new()?;
    let pwm = Pwm::new(Channel::Pwm0)?;

    let _ = pwm.set_frequency(50.0, 0.1);
    let _ = pwm.enable();
    let _ = pwm.set_polarity(Polarity::Normal);

    thread::sleep(Duration::from_secs(1));

    Ok(())
}
