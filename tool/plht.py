import yaml
import os


def parse_enum(name: str, data: dict[str, object], c_data: list[str], cpp_data: list[str], ns_prefix_c: str = ''):
  c_name = ns_prefix_c + name
  type_annotation = ''
  enum_values = []

  for item in data:
    if not item.startswith('?'):
      enum_values.append(item)
    if item.startswith('?type='):
      type_annotation = f" : {item[len('?type='):]}"
    if item.startswith('?c.name='):
      c_name = ns_prefix_c + item[len('?c.name='):]

  c_data.append(f'typedef enum {c_name} {{')
  cpp_data.append(f'enum class {name}{type_annotation} {{')

  for value in enum_values:
    c_value = value.replace('`', c_name + '_')
    cpp_value = value.replace('`', '')
    c_data.append(f'  {c_name}_{c_value},')
    cpp_data.append(f'  {cpp_value},')

  c_data.append(f'}} {c_name};')
  cpp_data.append(f'}};')


def conditioned(v: str, c_gen, cpp_gen=None) -> str | tuple[str, str]:
  v = v.split('?')
  if cpp_gen is None:
    text = c_gen(v[0])
    for c in v[1:]:
      if c.startswith('if='):
        condition = c[3:]
        text = f'#if {condition}\n{text}\n#endif'
      elif c == 'c':
        cpp_text = ''
      elif c == 'cpp':
        c_text = ''
    return text
  else:
    c_text = c_gen(v[0])
    cpp_text = cpp_gen(v[0])
    for c in v[1:]:
      if c.startswith('if='):
        condition = c[3:]
        c_text = f'#if {condition}\n{c_text}\n#endif'
        cpp_text = f'#if {condition}\n{cpp_text}\n#endif'
      elif c == 'c':
        cpp_text = ''
      elif c == 'cpp':
        c_text = ''
    return c_text, cpp_text


def parse_namespace(name: str, data: dict[str, object], ns_prefix_c: str = '') -> tuple[str, str]:
  if name: ns_prefix_c += data.get('c.name', name) + '_'

  c_data = []
  cpp_data = []
  for k, v in data.items():
    if k.startswith('enum.'):
      enum_name = k.split('.')[1]
      parse_enum(enum_name, v, c_data, cpp_data, ns_prefix_c)
    if k.startswith('expr.'):
      k = k.split('.')[1]
      c_text, cpp_text = conditioned(v, lambda v: f'#define {k} ({v})' if ' ' in v else f'#define {k} {v}', lambda v: f'constexpr auto {k} = {v};')
      c_data.append(c_text)
      cpp_data.append(cpp_text)
    elif k.startswith('ns.'):
      ns_name = k.split('.')[1]
      c_str, cpp_str = parse_namespace(ns_name, v, ns_prefix_c)
      c_data.append(c_str)
      cpp_data.append(cpp_str)
    elif k.startswith('.'):
      c_str, cpp_str = parse_namespace('', v, ns_prefix_c)
      c_data.append(c_str)
      cpp_data.append(cpp_str)
    elif not '.' in k and k != 'if':
      text = conditioned(v, lambda v: f'#define {k} {v}')
      c_data.append(text)
      cpp_data.append(text)

  c_data = '\n'.join(c_data)
  cpp_data = '\n'.join(cpp_data)

  if name: cpp_data = f'namespace {name} {{\n{cpp_data}\n}};'

  if 'if' in data:
    c = data['if']
    if isinstance(c, str):
      c_data = f'#if {c}\n{c_data}\n#endif'
      cpp_data = f'#if {c}\n{cpp_data}\n#endif'
    else:
      for condition in c:
        c_data = f'#if {condition}\n{c_data}\n#endif'
        cpp_data = f'#if {condition}\n{cpp_data}\n#endif'

  return c_data, cpp_data


def convert(yaml_file):
  with open(yaml_file, 'r') as file:
    data = yaml.safe_load(file)
    print(data)

  c_data, cpp_data = parse_namespace('', data)

  c_data = '// This file is automatically generated, please do not modify it.\n#pragma once\n' + c_data
  cpp_data = '// This file is automatically generated, please do not modify it.\n#pragma once\n' + cpp_data

  return c_data, cpp_data


def get_files_with_extensions(folder_path: str | list[str], extensions: str | list[str]):
  file_list = []
  if isinstance(extensions, str):
    extensions = [extensions]
  if isinstance(folder_path, list):
    for path in folder_path:
      file_list += get_files_with_extensions(path, extensions)
    return file_list
  for root, dirs, files in os.walk(folder_path):
    for file in files:
      if '.' in file:
        file_extension = file.split('.')[-1].lower()
        if file_extension in extensions:
          file_list.append(os.path.join(root, file))
  return file_list


if __name__ == "__main__":
  for filename in get_files_with_extensions('.', ['plht']):
    print(filename)
    c_data, cpp_data = convert(filename)
    with open(filename[:-4] + 'h', 'w') as file:
      file.write(c_data)
    with open(filename[:-4] + 'hpp', 'w') as file:
      file.write(cpp_data)
