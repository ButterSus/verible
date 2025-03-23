# Enhanced Verible Formatter for Arch Linux

This repository contains a modified version of the Verible SystemVerilog formatter with enhanced named port and parameter alignment features.

## Named Port and Parameter Alignment Options

This fork enhances the formatter with three distinct alignment options for both named ports and parameters:

- `align-both`: Aligns both names and parentheses without any extra spaces
- `align-both-spaced`: Aligns both names and parentheses with a space before opening parenthesis, but no spaces inside
- `align-both-separated`: Aligns both names and parentheses with spaces both before the opening parenthesis and inside the parentheses

By default, when using the enhanced alignment options, `align-both-spaced` is used as the default style.

### Port Connection Examples

Original code:
```verilog
module test;
  my_module instance_name (
    .parameter1(value1),
    .parameter_with_long_name(value_with_long_name),
    .short_param(short_val)
  );
endmodule
```

With `--named_port_alignment=align-both`:
```verilog
module test;
  my_module instance_name (
      .parameter1              (value1              ),
      .parameter_with_long_name(value_with_long_name),
      .short_param             (short_val           )
  );
endmodule
```

With `--named_port_alignment=align-both-spaced`:
```verilog
module test;
  my_module instance_name (
      .parameter1               (value1              ),
      .parameter_with_long_name (value_with_long_name),
      .short_param              (short_val           )
  );
endmodule
```

With `--named_port_alignment=align-both-separated`:
```verilog
module test;
  my_module instance_name (
      .parameter1               ( value1               ),
      .parameter_with_long_name ( value_with_long_name ),
      .short_param              ( short_val            )
  );
endmodule
```

### Parameter Assignment Examples

The same alignment options are also available for named parameter assignments:

Original code:
```verilog
module test;
  my_module #(
    .PARAM1(100),
    .PARAMETER_WITH_LONG_NAME(VALUE_WITH_LONG_NAME),
    .SHORT_PARAM(5)
  ) instance_name();
endmodule
```

With `--named_parameter_alignment=align-both`:
```verilog
module test;
  my_module #(
      .PARAM1                  (100                  ),
      .PARAMETER_WITH_LONG_NAME(VALUE_WITH_LONG_NAME),
      .SHORT_PARAM             (5                    )
  ) instance_name();
endmodule
```

With `--named_parameter_alignment=align-both-spaced`:
```verilog
module test;
  my_module #(
      .PARAM1                   (100                  ),
      .PARAMETER_WITH_LONG_NAME (VALUE_WITH_LONG_NAME),
      .SHORT_PARAM              (5                    )
  ) instance_name();
endmodule
```

With `--named_parameter_alignment=align-both-separated`:
```verilog
module test;
  my_module #(
      .PARAM1                   ( 100                   ),
      .PARAMETER_WITH_LONG_NAME ( VALUE_WITH_LONG_NAME  ),
      .SHORT_PARAM              ( 5                     )
  ) instance_name();
endmodule
```

## Installation (Arch Linux)

To install the enhanced Verible formatter on Arch Linux:

```bash
# Create a build directory
mkdir -p ~/build/verible-buttersus
cd ~/build/verible-buttersus

# Download the PKGBUILD
curl -O https://raw.githubusercontent.com/ButterSus/verible/pkgbuild/PKGBUILD

# Build and install the package
makepkg -si
```

## Usage

After installation, you can use any of the alignment options:

```bash
# For named port alignment
verible-verilog-format --named_port_alignment=align-both your_file.sv
verible-verilog-format --named_port_alignment=align-both-spaced your_file.sv
verible-verilog-format --named_port_alignment=align-both-separated your_file.sv

# For named parameter alignment
verible-verilog-format --named_parameter_alignment=align-both your_file.sv
verible-verilog-format --named_parameter_alignment=align-both-spaced your_file.sv
verible-verilog-format --named_parameter_alignment=align-both-separated your_file.sv
```

## For Developers

### Create the pkgbuild Branch

Create an orphan branch with just the PKGBUILD and README:

```bash
# Clone the repository if you haven't already
git clone https://github.com/ButterSus/verible.git
cd verible

# Create a new orphan branch
git checkout --orphan pkgbuild

# Remove all files from the working directory
git rm -rf .

# Add the PKGBUILD and README.md files
# (Create these files as shown in this repository)

# Commit and push
git add PKGBUILD README.md
git commit -m "Add PKGBUILD for enhanced Verible formatter"
git push origin pkgbuild
``` 