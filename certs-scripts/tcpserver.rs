use std::io::prelude::*;
use std::net::{TcpListener, TcpStream, Shutdown};
use std::sync::mpsc;
use std::io::BufReader;
use std::thread;
use std::str;


fn listen(tx_pipe: mpsc::Sender<u32>){
    let listener = TcpListener::bind("127.0.0.1:7777").unwrap();

    for stream in listener.incoming(){
        match stream{
            Ok(stream)  => {
                println!("Received a connection! - {}:{}", stream.peer_addr().unwrap().ip(), stream.peer_addr().unwrap().port());
                let txp = tx_pipe.clone();
                thread::spawn(move || {
                    connect_handler(stream, txp);
                });
                tx_pipe.send(1).unwrap();
            }
            Err(e)      => println!("Error! - {}", e)
        }
    }

    drop(listener);
}

fn connect_handler(stream: TcpStream, tx_pipe: mpsc::Sender<u32>){
    let mut buf = BufReader::new(stream.try_clone().unwrap());
    loop{
        //let mut s = [0u8; 4096];
        let mut s = String::new();
        match buf.read_line(&mut s){
            Ok(b)  => {
                if b == 0 { break; }
                print!("Received data ({} bytes): {}", b, s);
                if s.contains("quit"){
                    tx_pipe.send(2).unwrap();
                    break;
                }
                //println!("Received data ({} bytes): {}", b, std::str::from_utf8(&s).unwrap())
            }
            Err(e) => println!("Error receiving data! - {}", e)
        }
    }

    println!("Client {}:{} dropped", stream.peer_addr().unwrap().ip(), stream.peer_addr().unwrap().port());
    stream.shutdown(Shutdown::Both).unwrap();
}

fn main(){
    println!("Initializing");
    println!("Ctrl+C to exit");

    let (channel_tx, channel_rx) = mpsc::channel();
    
    let tx_pipe = channel_tx.clone();
    thread::spawn(move || { listen(tx_pipe); });
 
    let mut connections = 0;
    loop{
        match channel_rx.recv(){
            Ok(signal)  => {
                match signal{
                    1 => connections += 1,
                    2 => break,
                    _ => println!("Invalid signal received: {}", signal)
                }
            }
            Err(e)      => {
                println!("Pipe broken - {}", e);
            }
        }
    }

    println!("Total connections: {}", connections);
    println!("Exiting");
}
