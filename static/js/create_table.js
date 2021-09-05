
		function loadData(data) {

			console.log("処理開始");

			// テーブル表示リセット
			$("#syain tr,#syain th").remove();

			// タイトル専用
			var title_row;
			var title_col_data;
			// データ用
			var row_data;
			var col_data;

			// 行のループ  ( <tr></tr> )
			$.each(data, function (index, value) {

				// 初回はタイトル作成
				if (index == 0) {
					$.each(value, function (key, val) {
						title_col_data = $("<th></th>").appendTo("#syain");
						title_col_data.text(key);
					});
				}

				// テーブルに行を追加   
				row_data = $("<tr></tr>").appendTo("#syain");

				// 列のループ ( <td></td> )
				$.each(value, function (key, val) {

					// 行に列を追加
					col_data = $("<td></td>").appendTo(row_data);
					col_data.text(val);

				});

			});

		}