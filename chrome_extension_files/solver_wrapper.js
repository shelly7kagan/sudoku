import initWasmModule from './solving_algorithm.js';

function readBoard(){
  const table = document.getElementById('puzzle_grid');
  const tableData = [];

  if (table) {
    const rows = table.getElementsByTagName('tr');
    
    for (let i = 0; i < rows.length; i++) {
      const cells = rows[i].getElementsByTagName('td');
      const rowData = [];
      
      for (let j = 0; j < cells.length; j++) {
        const input = cells[j].getElementsByTagName('input')[0];
        if (input && input.value != '') {
          rowData.push(parseInt(input.value));
        } else {
          rowData.push(0);
        }
      }
      
      tableData.push(rowData);
    }
  }
  return tableData;
}

initWasmModule().then((module) => {
  // Use your WebAssembly module here
});


const tableData = readBoard();
console.log(tableData);