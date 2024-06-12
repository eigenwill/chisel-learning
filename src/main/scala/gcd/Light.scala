import chisel3._
// _root_ disambiguates from package chisel3.util.circt if user imports chisel3.util._
import _root_.circt.stage.ChiselStage

/**
  * Compute GCD using subtraction method.
  * Subtracts the smaller from the larger until register y is zero.
  * value in register x is then the GCD
  */
class Light extends Module {
  val io = IO(new Bundle {
    val outputLed = Output(UInt(16.W))
  })

  val count = RegInit(0.U(32.W))
  val led = RegInit(1.U(16.W))

  count := Mux(count === 5000000.U, 0.U, count + 1.U)

  when(count === 0.U) {
    led := led(14, 0) ## led(15)
  }

  io.outputLed := led
  
}

/**
 * Generate Verilog sources and save it in file GCD.v
 */
object Light extends App {
  ChiselStage.emitSystemVerilogFile(
    new Light,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info")
  )
}
