
// selecte = document.getElementById("mySelect");
// select = document.getElementById("myStatus");
// is_doc = document.getElementById("doc");
// is_img = document.getElementById("img");
// count = document.getElementById("count");

$(document).ready(function () {
  // dat = document.getElementById("dat");
  // name = document.getElementById("name");
  searchName = document.getElementById("searchName");
  searchDate = document.getElementById("searchDate");
  streets = document.getElementById("streets");
  countStreets = document.getElementById("countStreets")
      function search_street() {
      // alert(searchName.value);
      // alert(searchDate.value);
      $.ajax({
            type: 'GET',
            async: true,
            url: "ajax/",
            data:  {
              'searchDate': searchDate.value,
              'searchName': searchName.value,
            },
            success: function(data) {
              createTable(data);
              countStreets.innerHTML = "Кількість вулиць: " + data.length
            },
            dataType: 'json',
        });
    }
    search_street();
  // $('#mySelect').change(function(){
  //     search_street();
  //   });
  //
  //   $('#myStatus').change(function(){
  //       search_street();
  //     });

  // $('#doc').change(function(){
  //     search_street();
  //   });
  // $('#img').change(function(){
  //     search_street();

  $('#searchName').keyup(function(){
    search_street();
  });

  $('#searchDate').change(function(){
    search_street();
  });


  function createTable(data) {
    table = `
    <thead>
     <tr class="w3-black">
       <th>Номер у б/д</th>
       <th>Назва вулиці</th>
       <th>Тип вулиці</th>
     </tr>
   </thead>
    `

    var i = 0;
    while(i < data.length && i < 100) {
      table += `
      <tr>
        <td>${data[i][0]}</td>
        <td><a href="/${data[i][0]}/">${data[i][1]}</a></td>
        <td>${data[i][2]}</td>
      </tr>
      `
      i++;
    }

    // var col = [];
    //       for (var i = 0; i < data.length; i++) {
    //           for (var key in data[i]) {
    //               if (col.indexOf(key) === -1) {
    //                   col.push(key);
    //               }
    //           }
    //       }
    //
    //       // CREATE DYNAMIC TABLE.
    //       var table = document.createElement("table");
    //
    //       // CREATE HTML TABLE HEADER ROW USING THE EXTRACTED HEADERS ABOVE.
    //
    //       var tr = table.insertRow(-1);                   // TABLE ROW.
    //
    //       for (var i = 0; i < col.length; i++) {
    //           var th = document.createElement("th");      // TABLE HEADER.
    //           th.innerHTML = col[i];
    //           tr.appendChild(th);
    //       }
    //
    //       // ADD JSON DATA TO THE TABLE AS ROWS.
    //       for (var i = 0; i < data.length; i++) {
    //
    //           tr = table.insertRow(-1);
    //
    //           for (var j = 0; j < col.length; j++) {
    //               var tabCell = tr.insertCell(-1);
    //               tabCell.innerHTML = data[i][col[j]];
    //           }
    //       }

          streets.innerHTML = table;
  }
    });
