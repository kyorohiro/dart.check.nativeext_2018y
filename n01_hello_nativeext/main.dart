library test_sample_extension;

import './libhello.dart';

void main(List<String> args) {
  print("##1+2=${sum(1, 2)}");
  try {
    print("## null+2=${sum(null, 2)}");
  } catch (e) {
    print("## null+2=error(${e})");
  }
}
